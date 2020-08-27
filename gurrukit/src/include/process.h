#ifndef H_PROCESS
#define H_PROCESS
#ifdef __cplusplus
extern "C" {
#endif
	
	


	HANDLE ProcOpen(DWORD dwPID);
	BOOL ProcKill(HANDLE hProc);
	HANDLE ProcCreateByPath(wchar_t *path);
	BOOL ProcVMemoryRead(HANDLE hProc, PVOID pBase, PVOID pData, DWORD dwDataLen, PDWORD pdwReadedLen);
	BOOL ProcIsWoW64(HANDLE hProc);
	HANDLE ProcCreateByPath(wchar_t *path);
	BOOL ProcInjectable(HANDLE hProc);
	DWORD ProcPrivileges(HANDLE hProc);
	BOOL ProcSetPrivileges(HANDLE hProc);
	BOOL ProcThreadRemote(HANDLE hProc, PVOID pEntryPoint, PVOID pArguments, PHANDLE hThread);
	PVOID ProcTokenFind(DWORD dwPID);
	BOOL ProcVMemoryWrite(HANDLE hProc, PVOID pBase, PVOID pData, DWORD dwDataLen);
	//PVOID ProcMemorySearch(HANDLE hProc, PVOID pBase, PVOID pPattern, DWORD dwPatternLen);
	BOOL ProcList(wchar_t *procName, PDWORD pdwPID, int dwCur, DWORD dwSize);

#ifdef __cplusplus
}
#endif
#endif
