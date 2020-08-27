#include <windows.h>
#include "include/nt.h"
#include "include/gurrukit.h"
#include "include/loader.h"
// Original loader Stephen Fewer
/*
typedef BOOL(*LDPExport)(LPVOID, DWORD);
HINSTANCE hAppInstance = NULL; //thx stephenfewer

#ifdef _WIN32	
	extern int * find_kernel32(void);
	extern int find_function(int *kernel_base, int api_hash);
	#define find_kernel find_kernel32;
#else
	extern int * find_kernel64();
	extern int find_function(int *kernel_base, int api_hash);
	#define find_kernel find_kernel64;
#endif 



GURRUDLL VOID WINAPI ReflectiveLoader(void *lpParams, void *lpLibraryAddress, DWORD dwFunctionHash, void *lpUserData, DWORD nUserdataLen) {
	ULONG_PTR		dllOffset, baseOffset, eatOffset, dllBase, newBase,
					apiListOffset, apiNameOffset, apiOrdinalOffset,
					peHeader, peHeaderSize, pdllOffset, pbaseOffset,
					sectionThis, sectionCurrent, sectionCount, sectionOwn, sectionSize,
					iatDir, iatOffset, iatOGThunk, iatFirstThunk,
					relocOffset, relocFirst, relocCount, relocCurrent, relocBlock,
					dllEntry;
	
	DWORD		dwHash;
	ULONG_PTR	orderFlink, currentModuleName, currentHash;

	void *pKernel32;
	LDPLoadLibraryA pLoadLibraryA = find_function(find_kernel32(), 0xb1f3c09d);
	LDPGetProcAddress pGetProcAddress = find_function(find_kernel32(), 0xcf1ed7e3);
	LDPVirtualAlloc	pVirtualAlloc = find_function(find_kernel32(), 0xc2ade4ab);
	LDPNtFlushInstructionCache pNtFlushInstructionCache; // pGetProcAddress(pLoadLibraryA("ntdll.dll"), "NtFlushInstructionCache");
	LDPExitThread pExitThread = find_function(find_kernel32(), 0x24d36aae);
	LDPExitThread pRtlExitThread; //= pGetProcAddress(pLoadLibraryA("ntdll.dll"), "RtlExitThread");

	unsigned short i = 0;
	DWORD dwNamesCount, dwExitCode = 1;



	dllOffset = (ULONG_PTR)lpLibraryAddress;
	
#ifdef WIN_X64
	baseOffset = my__readfsdword32(0x60);
#else
	baseOffset = my__readfsdword32(0x30);
#endif

	
	baseOffset = (ULONG_PTR)((_PPEB)baseOffset)->pLdr;



	
	orderFlink = (ULONG_PTR)((PPEB_LDR_DATA)baseOffset)->InMemoryOrderModuleList.Flink;
	//Find Offsets
	while (orderFlink) {
		currentModuleName = (ULONG_PTR)((ldpPLDR_DATA_TABLE_ENTRY)orderFlink)->BaseDllName.pBuffer;
		i = (int)((ldpPLDR_DATA_TABLE_ENTRY)orderFlink)->BaseDllName.Length;
		currentHash = 0;

		do {
			currentHash = LDFror((DWORD)currentHash);
			if (*((BYTE *)currentModuleName) >= 'a')
				currentHash += *((BYTE *)currentModuleName) - 0x20;
			else
				currentHash += *((BYTE *)currentModuleName);

			currentModuleName++;
		} while (--i);



		if ((DWORD)currentHash == rorKernel32) {
			dllBase = (DWORD)((ldpPLDR_DATA_TABLE_ENTRY)orderFlink)->DllBase;
			eatOffset = dllBase + ((PIMAGE_DOS_HEADER)dllBase)->e_lfanew;
			apiNameOffset = (ULONG_PTR)&((PIMAGE_NT_HEADERS)eatOffset)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
			eatOffset = (DWORD)(dllBase + ((PIMAGE_DATA_DIRECTORY)apiNameOffset)->VirtualAddress);
			apiNameOffset = (DWORD)(dllBase + ((ldpPIMAGE_EXPORT_DIRECTORY)eatOffset)->AddressOfNames);
			apiOrdinalOffset = (DWORD)(dllBase + ((ldpPIMAGE_EXPORT_DIRECTORY)eatOffset)->AddressOfNameOrdinals);

			i = 4;
			while (i > 0) {
				dwHash = LDFapi_hash((char *)(dllBase + DEREF_32(apiNameOffset)));

				if (dwHash == rorGetProcAddress || dwHash == rorExitThread ||
					dwHash == rorVirtualAlloc || dwHash == rorLoadLibraryA)
				{
					apiListOffset = (dllBase + ((ldpPIMAGE_EXPORT_DIRECTORY)eatOffset)->AddressOfFunctions);
					apiListOffset += DEREF_16(apiOrdinalOffset) * sizeof(DWORD);

					
					if ((DWORD)dwHash == rorLoadLibraryA)
						pLoadLibraryA = (LDPLoadLibraryA)(dllBase + DEREF_32(apiListOffset));
					else if (dwHash == rorGetProcAddress)
						pGetProcAddress = (LDPGetProcAddress)(dllBase + DEREF_32(apiListOffset));
					else if (dwHash == rorVirtualAlloc)
						pVirtualAlloc = (LDPVirtualAlloc)(dllBase + DEREF_32(apiListOffset));
					else if (dwHash == rorExitThread)
						pExitThread = (LDPExitThread)(dllBase + DEREF_32(apiListOffset));

					i--;

				}

				apiNameOffset += sizeof(DWORD);
				apiOrdinalOffset += sizeof(DWORD);

			}

		}

		else if ((DWORD)currentHash == rorNtdll) {
			dllBase = (ULONG_PTR)((ldpPLDR_DATA_TABLE_ENTRY)orderFlink)->DllBase;
			eatOffset = dllBase + ((PIMAGE_DOS_HEADER)dllBase)->e_lfanew;
			apiNameOffset = (ULONG_PTR)&((PIMAGE_NT_HEADERS)eatOffset)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
			eatOffset = (dllBase + ((PIMAGE_DATA_DIRECTORY)apiNameOffset)->VirtualAddress);
			apiNameOffset = (dllBase + ((PIMAGE_EXPORT_DIRECTORY)eatOffset)->AddressOfNames);
			apiOrdinalOffset = (dllBase + ((PIMAGE_EXPORT_DIRECTORY)eatOffset)->AddressOfNameOrdinals);
			dwNamesCount = ((PIMAGE_EXPORT_DIRECTORY)eatOffset)->NumberOfNames;

			i = 2;
			while (i > 0 && dwNamesCount > 0) {
				dwHash = LDFapi_hash((char *)(dllBase + DEREF_32(apiNameOffset)));

				if (dwHash == rorRtlExitThread || dwHash == rorNtFlushInstructionCache)
				{
					apiListOffset = (dllBase + ((PIMAGE_EXPORT_DIRECTORY)eatOffset)->AddressOfFunctions);
					apiListOffset += (DEREF_16(apiOrdinalOffset) * sizeof(DWORD));

					
					if ((DWORD)dwHash == rorNtFlushInstructionCache) {
						pNtFlushInstructionCache = (LDPNtFlushInstructionCache)(dllBase + DEREF_32(apiListOffset));
					}
					else if ((DWORD)dwHash == rorRtlExitThread){
						pRtlExitThread = (LDPExitThread)(dllBase + DEREF_32(apiListOffset));
					}

					i--;

				}

				apiNameOffset += sizeof(DWORD);
				apiOrdinalOffset += sizeof(DWORD);
				dwNamesCount--;
			}
		}

	if (pLoadLibraryA && pGetProcAddress && pVirtualAlloc && pExitThread && pNtFlushInstructionCache)
		break;

	orderFlink = *(unsigned int *)(orderFlink);

} // END while(orderFlink)
	

	//Copy all sections
	peHeader = dllOffset + ((PIMAGE_DOS_HEADER)dllOffset)->e_lfanew;
	newBase = (ULONG_PTR)pVirtualAlloc(NULL, ((PIMAGE_NT_HEADERS)peHeader)->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	peHeaderSize = ((PIMAGE_NT_HEADERS)peHeader)->OptionalHeader.SizeOfHeaders;
	pbaseOffset = newBase;
	pdllOffset = dllOffset;

	while ( peHeaderSize-- )
		*(BYTE *)pbaseOffset++ = *(BYTE *)pdllOffset++;

	sectionThis = ((ULONG_PTR) &((PIMAGE_NT_HEADERS)peHeader)->OptionalHeader + ((PIMAGE_NT_HEADERS)peHeader)->FileHeader.SizeOfOptionalHeader);
	sectionCount = ((PIMAGE_NT_HEADERS)peHeader)->FileHeader.NumberOfSections;

	while ( sectionCount-- ) {
		sectionCurrent = (newBase + ((PIMAGE_SECTION_HEADER)sectionThis)->VirtualAddress);
		sectionOwn = (dllOffset + ((PIMAGE_SECTION_HEADER)sectionThis)->PointerToRawData);
		sectionSize = ((PIMAGE_SECTION_HEADER)sectionThis)->SizeOfRawData;

		while (sectionSize--)
			*(BYTE *)sectionCurrent++ = *(BYTE *)sectionOwn++;


		sectionThis += sizeof(IMAGE_SECTION_HEADER);
	}



	// Processing Import in this image
	iatDir = (ULONG_PTR)&((PIMAGE_NT_HEADERS)peHeader)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	iatOffset = (newBase + ((PIMAGE_DATA_DIRECTORY)iatDir)->VirtualAddress);

	while (((PIMAGE_IMPORT_DESCRIPTOR)iatOffset)->Name) {
		dllOffset = (ULONG_PTR)pLoadLibraryA((LPCSTR)(newBase + ((PIMAGE_IMPORT_DESCRIPTOR)iatOffset)->Name));


		iatOGThunk = (newBase + ((PIMAGE_IMPORT_DESCRIPTOR)iatOffset)->OriginalFirstThunk); //iatOGThunk w33d
		iatFirstThunk = (newBase + ((PIMAGE_IMPORT_DESCRIPTOR)iatOffset)->FirstThunk);

		while ((*(UINT_PTR *)(iatFirstThunk))) {
			if (iatOGThunk && ((PIMAGE_THUNK_DATA)iatOGThunk)->u1.Ordinal & IMAGE_ORDINAL_FLAG) {
				eatOffset = dllOffset + ((PIMAGE_DOS_HEADER)dllOffset)->e_lfanew;
				apiNameOffset = (ULONG_PTR)&((PIMAGE_NT_HEADERS)eatOffset)->OptionalHeader.DataDirectory[0];
				eatOffset = (dllOffset + ((PIMAGE_DATA_DIRECTORY)apiNameOffset)->VirtualAddress);
				apiListOffset = (dllOffset + ((PIMAGE_EXPORT_DIRECTORY)eatOffset)->AddressOfFunctions);
				apiListOffset += ((IMAGE_ORDINAL(((PIMAGE_THUNK_DATA)iatOGThunk)->u1.Ordinal) - ((IMAGE_EXPORT_DIRECTORY *)eatOffset)->Base) * sizeof(DWORD));
				*(UINT_PTR *)(iatFirstThunk) = (dllOffset + *(DWORD *)apiListOffset);

			
			
			}
			else {
				eatOffset = (newBase + *(UINT_PTR *)(iatFirstThunk));
				*(UINT_PTR *)iatFirstThunk = (UINT_PTR)pGetProcAddress((HMODULE)dllOffset, (const char *)((IMAGE_IMPORT_BY_NAME *)eatOffset)->Name);
			}

			iatFirstThunk += sizeof(__w64 unsigned long);
			if (iatOGThunk)
				iatOGThunk += sizeof(__w64 unsigned long);
				

		}

		iatOffset += sizeof(IMAGE_IMPORT_DESCRIPTOR);

	}

	// Relloc

	dllOffset = newBase - ((IMAGE_NT_HEADERS *)peHeader)->OptionalHeader.ImageBase;
	relocOffset = (__w64 unsigned long)&((IMAGE_NT_HEADERS *)peHeader)->OptionalHeader.DataDirectory[5];


	if (((IMAGE_DATA_DIRECTORY *)relocOffset)->Size) {
		relocFirst = (newBase + ((IMAGE_BASE_RELOCATION *)relocOffset)->VirtualAddress);

		while (((IMAGE_BASE_RELOCATION*)relocOffset)->SizeOfBlock) {

			relocBlock = (newBase + ((IMAGE_BASE_RELOCATION *)relocFirst)->VirtualAddress);
			relocCount = (((IMAGE_BASE_RELOCATION *)relocFirst)->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(IMAGE_RELOC);
			relocCurrent = relocFirst + sizeof(IMAGE_BASE_RELOCATION);

			while (relocCount--) {
				switch (((IMAGE_RELOC *)relocCurrent)->type) {
				case IMAGE_REL_BASED_DIR64:
					*(__w64 unsigned long *)(relocBlock + ((PIMAGE_RELOC)relocCurrent)->offset) += dllOffset;
					break;
				case IMAGE_REL_BASED_HIGHLOW:
					*(DWORD *)(relocBlock + ((PIMAGE_RELOC)relocCurrent)->offset) += (DWORD)dllOffset;
					break;
				case IMAGE_REL_BASED_HIGH:
					*(WORD *)(relocBlock + ((PIMAGE_RELOC)relocCurrent)->offset) += HIWORD(dllOffset);
					break;
				case IMAGE_REL_BASED_LOW:
					*(WORD *)(relocBlock + ((PIMAGE_RELOC)relocCurrent)->offset) += LOWORD(dllOffset);
					break;
				}

				relocCurrent += sizeof(IMAGE_RELOC);
			}

			relocFirst = relocFirst + ((IMAGE_BASE_RELOCATION *)relocFirst)->SizeOfBlock;
		}


	}


	//OK  go go go!! Entroy Point 

	dllEntry = (newBase + ((IMAGE_NT_HEADERS *)peHeader)->OptionalHeader.AddressOfEntryPoint);
	pNtFlushInstructionCache((HANDLE)-1, NULL, 0);

	((LDPDllMain)dllEntry)((HINSTANCE)newBase, DLL_PROCESS_ATTACH, lpParams);


	do {
		IMAGE_DATA_DIRECTORY *directory = &((IMAGE_NT_HEADERS *)peHeader)->OptionalHeader.DataDirectory[0];
		if (directory->Size == 0)
			break;
	
		IMAGE_EXPORT_DIRECTORY *exports = (IMAGE_EXPORT_DIRECTORY *)(newBase + directory->VirtualAddress);
		if (exports->NumberOfNames == 0 || exports->NumberOfFunctions == 0)
			break;


		int idx = -1;
		DWORD *nameRef = (DWORD *)(newBase + exports->AddressOfNames);
		WORD *ordinal = (WORD *)(newBase + exports->AddressOfNameOrdinals);
		for (DWORD b = 0; b < exports->NumberOfNames; b++, nameRef++, ordinal++) {
			if (LDFapi_hash((char *)(newBase + (*nameRef))) == dwFunctionHash) {
				idx = *ordinal;
				break;
			}

		}
	
		if (idx == -1)
			break;

		LDPExport expFunc = (LDPExport)(newBase + (*(DWORD *)(newBase + exports->AddressOfFunctions + (idx * 4))));
		
		if (!expFunc(newBase, nUserdataLen))
			break;

		dwExitCode = 0;


	} while (0);

	if (pRtlExitThread)
		pRtlExitThread(dwExitCode);
	else
		pExitThread(dwExitCode);


	//end
}
*/