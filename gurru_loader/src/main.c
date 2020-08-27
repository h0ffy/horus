//gurru!VX\\JennyLab
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wchar.h>
#include <winternl.h>
#include <wininet.h>
#include "include/api.h"
#include "include/security.h"
//#include "cc_control.h"
	//#include "cc_http.h"
//#include "cmd.h"
//#include "inject.h"
//#include "process.h"
//#include "payloads.h"
//#include "utils.h"
//#include "crypto.h"


//#pragma comment(lib,"ntdll.lib")
//#pragma comment(lib, "kernel32.lib")
//#pragma comment(lib, "user32.lib")
//#pragma comment(lib, "wininet.lib")
#pragma comment(lib "wininet")

void lInitialize(void);

int main(void) {
	//lInitialize
	//lSecurity();
	//lCC_Monitor();
	MessageBoxW(GetForegroundWindow(), L"Test it", L"gurru VX starting...", SW_SHOW);	
	__security_ntinfothread();
	wprintf(L"Test: %s\n", L"lalala");
	ExitProcess(0x00);	
	return 0;
}


void lInitialize(void) {
	return;
}



void copyright() {
	#if defined(_MSC_VER)
		__asm {
			push 0x68
			push 0x6f
			push 0x72
			push 0x75
			push 0x73
		}
	#else
		__asm("push 0x68");
		__asm("push 0x6f");
		__asm("push 0x72");
		__asm("push 0x75");
		__asm("push 0x73");
	#endif
}
