#ifndef H_MISC
#define H_MISC

#ifdef __cplusplus 
extern "C" {
#endif
	BOOL isGurru64;


	#define AnsiToUnicode(lpMultibyteStr, dwMultibyteLen, lpWideCharStr, lpdwWideCharLen) MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpMultibyteStr, dwMultibyteLen, lpWideCharStr, lpdwWideCharLen);
	#define	ERROR_WSTR L"ERROR"





	void swap(BYTE *data, DWORD val1, DWORD val2);
	extern ULONG nGetCPUID(void);
	extern BYTE random_byte(ULONG val1, UINT val2, UINT val3);
	extern void GetCPUID(wchar_t *wCPUID);
	extern BOOL iswOw64(void);
	BYTE random_byte2(void);

#ifdef __cplusplus
}
#endif
#endif