#ifndef H_MEMORY
#define H_MEMORY

#ifdef __cplusplus 
extern "C" {
#endif

	
	LPVOID LocalMemoryAlloc(DWORD dwNumberOfBytes);
	VOID LocalMemoryFree(LPVOID lpMemoryOffset);
	LPVOID MemoryAlloc(DWORD dwNumberOfBytes);
	VOID MemoryFree(LPVOID lpMemoryOffset);
	LPVOID MemoryReAlloc(LPVOID lpMemoryOffset, DWORD dwNumberOfBytes);
	BOOL MemoryVirtualFree(PVOID pMemory, DWORD dwNumberOfBytes);
	PVOID MemoryVirtualAlloc(DWORD dwNumberOfBytes);

#ifdef __cplusplus
}
#endif
#endif