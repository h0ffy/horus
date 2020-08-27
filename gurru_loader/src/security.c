#include <windows.h>
#include <winternl.h>
#include "include/api.h"
#include "include/security.h"


int lSecurity() {
	
	return(0);
}



int __security_int() {
	#ifdef _W64
		return(-1);
	#endif
	#if defined(_MSC_VER)
		__asm {
			int 0x03
			xor eax, eax
			mov al, 0
			int 0x2a
		}	
	#else
		__asm("int $0x03");
		__asm("xorl %eax, %eax");
		__asm("xorb 0, %al");
		__asm("int $0x2a");
	#endif
	return(0);
}

void __security_ntinfothread() {
        l_NtQueryInformationThread = (void *)GetProcAddress(LoadLibraryA("ntdll.dll"), "ZwSetInformationThread");
        l_NtQueryInformationThread(GetCurrentThread(), 0x11, 0x00, 0x00, 0x00);
}

void  __security_closehandle() {
	CloseHandle((HANDLE)0x737c);
}


void __security_isdebuggerpresent() {
	void *addr = GetProcAddress(LoadLibraryA("kernel32.dll"), "IsDebuggerPresent");
	void (*isdbg)() = addr;
	
	isdbg();	
}

/**
 * @brief 	Test if PC emulation x86 (some emulators no emulate the stack)
		in this case push NOPs and RET for call this and ret to continue or crash if not available stack
*/
void  __security_antiemu() {
	#if defined(_MSC_VER)
		#ifdef _W64
			__asm {
				push 0x3C
				push 0x90909090
				call esp
			}
		#else
			__asm {
				mov rax, 0x3C90909090909090
				mov rbx, 0x9090909090909090
				push rax
				push rbx
				call rsp

			}
		#endif
	#else
		#ifdef __x86_64
			__asm("movq $0x3c90909090909090, %rax");
			__asm("movq $0x9090909090909090, %rbx");
			__asm("pushq %rax");
			__asm("pushq %rbx");
			__asm("call *(%rsp)");
		#else
			__asm("push $0x3c909090");
			__asm("push $0x90909090");
			//__asm("push $0x3c");
			__asm("call *(%esp)");
		#endif
	#endif
	
}
