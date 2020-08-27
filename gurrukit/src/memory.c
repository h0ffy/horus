#include <windows.h>
#include <winternl.h>
#include "include/memory.h"

LPVOID MemoryAlloc(DWORD dwNumberOfBytes) {
	return(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwNumberOfBytes));
}


LPVOID MemoryReAlloc(LPVOID lpMemoryOffset, DWORD dwNumberOfBytes) {
	HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, lpMemoryOffset);
	return(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwNumberOfBytes));
}

VOID MemoryFree(LPVOID lpMemoryOffset) {
	HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, lpMemoryOffset);
	return;
}


LPVOID LocalMemoryAlloc(DWORD dwNumberOfBytes) {
	return(LocalAlloc(LPTR, dwNumberOfBytes));
}

VOID LocalMemoryFree(LPVOID lpMemoryOffset) {
	LocalFree(lpMemoryOffset);
	return;
}


PVOID MemoryVirtualAlloc(DWORD dwNumberOfBytes) {
	return(VirtualAlloc(NULL, dwNumberOfBytes, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
}

BOOL MemoryVirtualFree(PVOID pMemory, DWORD dwNumberOfBytes) {
	return(VirtualFree(pMemory, dwNumberOfBytes, MEM_RELEASE));
}