#ifndef H_CMD
#define H_CMD
#ifdef __cplusplus
extern "C" {
#endif
	#define CMD_MAX_ARGS 25
	#define CMD_MAX_ARGS_LEN 256
	#define CMD_MAX_COMMAND_LEN 256
	
	typedef struct _COMMAND_STRUCT {
		wchar_t *wCommand;
		wchar_t *wArgs[CMD_MAX_ARGS];
		wchar_t *wToken;
		DWORD dwArgsCount;
		BOOL bStatus;
	}CMD, *PCMD;


	typedef struct _CMDRPC_STRUCT {
		wchar_t *wCommand;
		int (__stdcall *cmdFunc)(PCMD *cmd);
	}CMDRPC, *PCMDRPC;


	PCMD CMDParser(wchar_t *wLine);
	BOOL CMDExecute(PCMD pCmd);
	VOID CMDFree(PCMD pCmd);



#ifdef __cplusplus
}
#endif
#endif