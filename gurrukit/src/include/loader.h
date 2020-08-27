#ifndef H_LOADER
#define H_LOADER
#ifdef __cplusplus 
extern "C" {
#endif

/*
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
//#include <Winsock2.h>
#include <intrin.h>
#include "nt.h"

GURRUDLL VOID WINAPI ReflectiveLoader(void *lpParams, void *lpLibraryAddress, DWORD dwFunctionHash, void *lpUserData, DWORD nUserdataLen);


typedef HMODULE		(WINAPI *LDPLoadLibraryA)(const char *);
typedef LPVOID		(WINAPI *LDPGetProcAddress)(HMODULE, const char *);
typedef LPVOID		(WINAPI *LDPVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
typedef VOID		(WINAPI *LDPExitThread)(DWORD);
typedef DWORD		(WINAPI *LDPNtFlushInstructionCache)(HANDLE, void *, ULONG);
typedef ULONG_PTR	(WINAPI * LDPloader)(void *);
typedef BOOL		(WINAPI * LDPDllMain)(HINSTANCE, DWORD, void *);

#define DEREF_32( name )*(DWORD *)(name)
#define DEREF_16( name )*(WORD *)(name)

// HASH DLL AND API
#define rorKey							13				// require 1 byte only
#define rorKernel32						0x6A4ABC5B 
#define rorNtdll						0x3CFA685D 

#define rorLoadLibraryA					0xEC0E4E8E
#define rorGetProcAddress				0x7C0DFCAA
#define rorVirtualAlloc					0x91AFCA54
#define rorExitThread					0x60E0CEEF
#define rorNtFlushInstructionCache		0x4d60196c		//0x534C0AB8
#define rorRtlExitThread				0xFF7F061A




#ifndef _MSC_VER
	__forceinline unsigned long my__readfsdword32(unsigned long val)
	{
	   unsigned long ret;
	   __asm__ volatile ("movl	%%fs:%1,%0"
		 : "=r" (ret) ,"=m" ((*(volatile long *) val)));
	   return ret;
	}
#else
	#define my__readfsdword32 __readfsdword
#endif

#pragma intrinsic(_rotr)
__forceinline DWORD LDFror(DWORD X) {
	//return _rotr(X, rorKey);
	//return((((X) >> (rorKey % 32)) | ((X) << (32 - (rorKey % 32)))));
	return (X >> rorKey) | (X << 32 - rorKey);

	int val;
	__asm {
		lea eax, X
		mov cl, rorKey
		ror eax, cl
		mov X, eax
	}
	//
	return(X);
}

__forceinline DWORD LDFapi_hash(char *c) { // thx. Dan Staples 
	register DWORD ret = 0;
	
	do
	{
		ret = LDFror(ret);
		ret += *c;
	} while (*++c);

	return ret;
}

#endif



typedef struct ldp_LDR_DATA_TABLE_ENTRY
{
	//LIST_ENTRY InLoadOrderLinks; // As we search from PPEB_LDR_DATA->InMemoryOrderModuleList we dont use the first entry.
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STR FullDllName;
	UNICODE_STR BaseDllName;
	ULONG Flags;
	SHORT LoadCount;
	SHORT TlsIndex;
	LIST_ENTRY HashTableEntry;
	ULONG TimeDateStamp;
} ldpLDR_DATA_TABLE_ENTRY, *ldpPLDR_DATA_TABLE_ENTRY;

typedef struct ldp_IMAGE_EXPORT_DIRECTORY {
	DWORD   Characteristics;
	DWORD   TimeDateStamp;
	WORD    MajorVersion;
	WORD    MinorVersion;
	DWORD   Name;
	DWORD   Base;
	DWORD   NumberOfFunctions;
	DWORD   NumberOfNames;
	DWORD   AddressOfFunctions;     // RVA from base of image
	DWORD   AddressOfNames;         // RVA from base of image
	DWORD   AddressOfNameOrdinals;  // RVA from base of image
} ldpIMAGE_EXPORT_DIRECTORY, *ldpPIMAGE_EXPORT_DIRECTORY;


*/

#ifdef __cplusplus
}
#endif
#endif
