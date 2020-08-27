#ifndef H_SDELETE
#define H_SDELETE
#ifdef __cplusplus
extern "C" {
#endif
		
	BYTE sdeleteGutmann(int pass);
	HANDLE sdeleteOpenFile(wchar_t *wFilePath);
	DWORD sdeleteWriteFile(HANDLE hFile, DWORD dwOffset, void *pBuff, ULONG uLen);
	void sdeleteCloseFile(HANDLE hFile);
	BOOL sdeleteDelFile(wchar_t *wFilePath);


#ifdef __cplusplus
}
#endif
#endif