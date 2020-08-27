#ifndef H_REPLY
#define H_REPLY
#ifdef __cplusplus
extern "C" {
#endif
	#define MAX_REPLY 0x666 + 0x333

	/*
		CONST OPTIONS
	*/
	#define	OPT_TO_SHELL	0x2
	#define OPT_TO_PROCESS	0x3
	#define OPT_TO_KEYPER	0x4
	#define OPT_TO_LIVE		0x5
	#define OPT_TO_BROWSER	0x6
	#define OPT_TO_TUNNEL	0x7

	#define OPTION_DEFAULT OPT_TO_SHELL


	typedef struct _ReplyStruct {
		DWORD dwOption;
		LPVOID vBuff;
		DWORD dwBuffLen;
		wchar_t *uToken;
		BOOL bStatus;
	}ReplyStruct, *PReplyStruct;



	BOOL ReplyUnLock(VOID);
	BOOL ReplyLock(VOID);
	int ReplyClean(VOID);
	LPVOID WINAPI ReplyExternal(LPVOID *lpParams);
	int ReplyPop(LPVOID vBuff, PDWORD dwBuffLen, wchar_t *uToken);
	int ReplyPush(DWORD dwOption, LPVOID vBuff, DWORD dwBuffLen, wchar_t *uToken);
	int ReplyPushStrW(DWORD dwOption, wchar_t *uToken, wchar_t *uFormatString, DWORD dwBuffLen, ...);
	int ReplyPushStrA(DWORD dwOption, char *iToken, char *iFormatString, DWORD dwBuffLen, ...);
	void ReplyInit(VOID);

	//#define PushA(iFormatString, dwBuffLen, ...) ReplyPushStrA(OPTION_DEFAULT, "", iFormatString, dwBuffLen, ...);
	#define PushW(uFormatString, dwBuffLen, ...) ReplyPushStrW(OPTION_DEFAULT, L"", uFormatString, dwBuffLen, ...);
	#define Push PushW
	#define REPLY_INIT() ReplyInit();

#ifdef __cplusplus
}
#endif
#endif