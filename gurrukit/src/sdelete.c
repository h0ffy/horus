#include <windows.h>
#include <winternl.h>
#include "include/misc.h"
#include "include/nt.h"
#include "include/memory.h"
#include "include/sdelete.h"



BOOL sdeleteDelFile(wchar_t *wFilePath) {
	int count = 255;
	HANDLE hFile;
	int pass = 0;
	DWORD dwOffset = 0L;
	BYTE nowByte = 0;
	ULONG dwSize = 0;
	hFile = sdeleteOpenFile(wFilePath);
	dwSize = sdeleteFileSize(hFile);
	sdeleteCloseFile(hFile);

	
	for (pass = 0; pass < 35; pass++) {
		dwOffset = 0;
		while (dwSize != dwOffset) {
			if ((hFile = sdeleteOpenFile(wFilePath)) == (HANDLE)0L)
				return(FALSE);

			nowByte = (BYTE)sdeleteGutmann((int)pass, dwOffset);
			sdeleteWriteFile(hFile, dwOffset, &nowByte, 1);
			dwOffset++;

			sdeleteCloseFile(hFile);
		}
	}
	return(TRUE);
}


ULONG sdeleteFileSize(HANDLE hFile) {
	DWORD dwLen = 2048;
	PFILE_STANDARD_INFO sFileInfo;
	IO_STATUS_BLOCK IoStatusBlock;
	ULONG uRet = 0L;

	sFileInfo = MemoryAlloc(2048);
	_NtQueryInformationFile(hFile, &IoStatusBlock, sFileInfo, dwLen, FileStandardInfo);

	uRet = (ULONG)sFileInfo->AllocationSize.QuadPart;

	return(uRet);
}


HANDLE sdeleteOpenFile(wchar_t *wFilePath) {
	OBJECT_ATTRIBUTES ObjAttributes;
	HANDLE hFile;
	IO_STATUS_BLOCK IoStatusBlock;
	UNICODE_STRING uString;
	ACCESS_MASK mask = DELETE | READ_CONTROL;

	
	InitializeObjectAttributes(&ObjAttributes, &uString, OBJ_CASE_INSENSITIVE, NULL, NULL);
	_RtlInitUnicodeString(&uString, wFilePath);
	

	//change to NtCreateFile 
	if (NT_STATUS(_NtOpenFile(&hFile, FILE_READ_ATTRIBUTES | SYNCHRONIZE, &ObjAttributes, &IoStatusBlock, FILE_SHARE_WRITE|FILE_SHARE_READ|FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT)))
		return((HANDLE)hFile);


	return(hFile);
}


void sdeleteCloseFile(HANDLE hFile) {
	_NtClose(hFile);
}


DWORD sdeleteWriteFile(HANDLE hFile, DWORD dwOffset, void *pBuff, ULONG uLen) {
	DWORD dwRet = 0;
	LARGE_INTEGER lInteger; 
	IO_STATUS_BLOCK IoStatusBlock;

	lInteger.QuadPart = uLen;


	if (NT_STATUS(_NtWriteFile(hFile, NULL, NULL, NULL, &IoStatusBlock, pBuff, uLen, &lInteger, NULL)))
		return(dwRet);

	dwRet = (DWORD)uLen;


	return dwRet;
}

BYTE sdeleteRandom(int pass) {
	return(random_byte(nGetCPUID(), 255, 0x796e654a));
}

BYTE sdeleteJennyLab(int pass) {
	const BYTE buff[] = "\x69JennyLab\xCC\x90\x3c";

	return(buff[pass / 7]);
}

BYTE sdeleteGutmann(int pass,DWORD dwOffset) {
	unsigned long tmp = 0L;

	switch (pass) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 32:
	case 33:
	case 34:
	case 35:
	default:
		return((BYTE)random_byte(nGetCPUID(), 255, 0x796e654a));
	case 5:
		return((BYTE)0x55);
	case 6:
		return((BYTE)0xAA);
	case 7:
	case 26:
		tmp = dwOffset % 3;
		switch (tmp) {
			case 0:
				return((BYTE)0x92);
			case 1:
				return((BYTE)0x49);
			case 2:
				return((BYTE)0x24);
			default:
				return((BYTE)random_byte(nGetCPUID(), 255, 0x796e654a));
		}
	case 8:
	case 27:
		tmp = dwOffset % 3;
		switch (tmp) {
		case 0:
			return((BYTE)0x49);
		case 1:
			return((BYTE)0x24);
		case 2:
			return((BYTE)0x92);
		default:
			return((BYTE)random_byte(nGetCPUID(), 255, 0x796e654a));
		}

	case 9:
	case 28:
		tmp = dwOffset % 3;
		switch (tmp) {
		case 0:
			return((BYTE)0x24);
		case 1:
			return((BYTE)0x92);
		case 2:
			return((BYTE)0x49);
		default:
			return((BYTE)random_byte(nGetCPUID(), 255, 0x796e654a));
		}
	case 10:
		return (BYTE)0x00;
	case 11:
		return (BYTE)0x11;
	case 12:
		return (BYTE)0x22;
	case 13:
		return (BYTE)0x33;
	case 14:
		return (BYTE)0x44;
	case 15:
		return (BYTE)0x55;
	case 16:
		return (BYTE)0x66;
	case 17:
		return (BYTE)0x77;
	case 18:
		return (BYTE)0x88;
	case 19:
		return (BYTE)0x99;
	case 20:
		return (BYTE)0xAA;
	case 21:
		return (BYTE)0xBB;
	case 22:
		return (BYTE)0xCC;
	case 23:
		return (BYTE)0xDD;
	case 24:
		return (BYTE)0xEE;
	case 25:
		return (BYTE)0xFF;
	case 29:
		tmp = dwOffset % 3;
		switch (tmp) {
		case 0:
			return((BYTE)0x6D);
		case 1:
			return((BYTE)0xB6);
		case 2:
			return((BYTE)0xDB);
		default:
			return((BYTE)random_byte(nGetCPUID(), 255, 0x796e654a));
		}


	case 30:
		tmp = dwOffset % 3;
		switch (tmp) {
		case 0:
			return((BYTE)0xB6);
		case 1:
			return((BYTE)0xDB);
		case 2:
			return((BYTE)0x6D);
		default:
			return((BYTE)random_byte(nGetCPUID(), 255, 0x796e654a));
		}


	case 31:
		tmp = dwOffset % 3;
		switch (tmp) {
		case 0:
			return((BYTE)0xB6);
		case 1:
			return((BYTE)0xDB);
		case 2:
			return((BYTE)0x6D);
		default:
			return((BYTE)random_byte(nGetCPUID(), 255, 0x796e654a));
		}

	}

	return((BYTE)0x00);
}