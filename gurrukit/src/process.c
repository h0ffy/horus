#include <windows.h>
#include <winternl.h>
#include "include/gurrukit.h"
#include "include/memory.h"
#include "include/misc.h"
#include "include/sys.h"
#include "include/nt.h"
#include "include/process.h"





HANDLE ProcOpen(DWORD dwPID) 	{ 
	OBJECT_ATTRIBUTES ObjAttributes;
	CLIENT_ID cID;
	HANDLE hProc;

	InitializeObjectAttributes(&ObjAttributes, NULL, 0, NULL, NULL);
	cID.UniqueProcess = (HANDLE)dwPID;
	cID.UniqueThread = 0;
	

	if (NT_STATUS(_NtOpenProcess(&hProc, PROCESS_ALL_ACCESS, &ObjAttributes, &cID))) {
		return((HANDLE)NULL);
	}

	return(hProc);

}			

BOOL ProcIsWoW64(HANDLE hProc) {
	ULONG_PTR uisWoW64;

	if (hProc==~0)
		return(iswOw64());

	if (!NT_STATUS(_NtQueryInformationProcess(hProc, ProcessWow64Information, &uisWoW64, sizeof(uisWoW64), NULL)))
		return(iswOw64());

	if (uisWoW64 != 0)
		return(TRUE);

	return(FALSE);
}

BOOL ProcKill(HANDLE hProc) {
	_NtTerminateProcess(hProc, 0);
	_NtClose(hProc);
	return TRUE;
}

BOOL ProcList(wchar_t *procName, PDWORD pdwPID, int dwCur, DWORD dwMaxSize) {
	PSYSTEM_PROCESS_INFO pInfo;
	DWORD dwInfoSize, dwNameSize;
	void *pBuff;
	int i = 0;

	while (NT_STATUS(_NtQuerySystemInformation(SystemProcessInformation, pBuff, dwInfoSize, &dwInfoSize)))
		pBuff = MemoryVirtualAlloc(dwInfoSize);

	pInfo = (PSYSTEM_PROCESS_INFO)pBuff;
	
	while (pInfo->NextEntryOffset) {
		if (i == dwCur) {
			if ((dwNameSize = lstrlenW(pInfo->ImageName.Buffer)) == 0) {
				wsprintf(procName, L"NT");
			}
			else {
				lstrcpynW(procName, pInfo->ImageName.Buffer, dwMaxSize);
			}
			pdwPID = pInfo->ProcessId;
			MemoryVirtualFree(pBuff, dwNameSize);
			return(TRUE);
		}
		

		pInfo = (PSYSTEM_PROCESS_INFO)((LPBYTE)pInfo + pInfo->NextEntryOffset);
		i++;
	}

	MemoryVirtualFree(pBuff, dwNameSize);
	return(FALSE);
}


HANDLE ProcCreateByPath(wchar_t *path) {return(NULL);}

BOOL ProcInjectable(HANDLE hProc) {	return TRUE; }
DWORD ProcPrivileges(HANDLE hProc) { return 0; }
BOOL ProcSetPrivileges(HANDLE hProc) { return TRUE; }
BOOL ProcThreadRemote(HANDLE hProc, PVOID pEntryPoint, PVOID pArguments, PHANDLE hThread) { return TRUE; }
PVOID ProcTokenFind(DWORD dwPID) { return NULL; }
BOOL ProcVMemoryWrite(HANDLE hProc, PVOID pBase, PVOID pData, DWORD dwDataLen) { return TRUE; }


BOOL ProcVMemoryRead(HANDLE hProc, PVOID pBase, PVOID pData, DWORD dwDataLen, PDWORD pdwReadedLen) { 
	DWORD dwReaded;
	
	if (NT_STATUS(_NtReadVirtualMemory(hProc, pBase, pData, dwDataLen, &dwReaded)))
		return(TRUE);

	return(FALSE); 

}
