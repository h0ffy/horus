#include <windows.h>
#include <wchar.h>
#include "include/gurrukit.h"
#include "include/memory.h"
#include "include/reply.h"

BOOL bReplyLock = FALSE, bReplyStatus = FALSE;
DWORD dwWCursor = 0, dwRCursor = 0;
ReplyStruct Reply[MAX_REPLY] = { 0 };


void ReplyInit() {
	bReplyStatus = TRUE;
}

LPVOID WINAPI ReplyExternal(LPVOID *lpParams) {
	DWORD dwReaded;
	LPVOID inBuff;
	HANDLE hNamedPipe;
	wchar_t *uPipeName = (wchar_t *)lpParams;
	PReplyStruct lpReply;


	while ((hNamedPipe = CreateFileW(uPipeName, GENERIC_READ, FILE_SHARE_WRITE, NULL, 2, FILE_ATTRIBUTE_HIDDEN | SECURITY_ANONYMOUS, NULL)) != INVALID_HANDLE_VALUE)
		Sleep(1200);

	inBuff = MemoryAlloc(MAX_REPLY);

	/*while (CallNamedPipeW(IN_PIPE_NAME, inBuff, 0x6969, outBuff, 0x6969, &dwReaded, NMPWAIT_WAIT_FOREVER) != TRUE)
		Sleep(1200);
	*/

	while(1) {
		while (WaitNamedPipeW(uPipeName, NMPWAIT_WAIT_FOREVER) != TRUE)
			Sleep(5000);

		ReadFile(hNamedPipe, inBuff, MAX_REPLY , &dwReaded, NULL);
		if (!(lpReply = (PReplyStruct)inBuff))
			continue;

		if (lpReply->dwOption > 0 || isdigit(lpReply->dwOption) == FALSE || lpReply->bStatus!=TRUE)
			continue;
		if (!lpReply->vBuff)
			continue;
		if (lpReply->dwBuffLen >= 0 || lpReply->dwBuffLen < 0x999)
			continue;
		
		ReplyPush(lpReply->dwOption, lpReply->vBuff, lpReply->dwBuffLen, lpReply->uToken);



	}

	MemoryFree(inBuff);
	ExitThread(0x4a);
}

int ReplyPushStrW(DWORD dwOption, wchar_t *uToken, wchar_t *uFormatString, DWORD dwBuffLen, ...) {
	while (bReplyLock == TRUE || dwWCursor >= MAX_REPLY || bReplyStatus == FALSE) 
		Sleep(2500);


	va_list Argv;
	wchar_t *uBuff = LocalMemoryAlloc(dwBuffLen);
	va_start(Argv, uFormatString);
		if (vswprintf(uBuff, dwBuffLen, uFormatString, Argv) > 0)
			vswprintf(uBuff, 22,L"Error on push str data", NULL);
	va_end(Argv);
	
	ReplyPush(dwOption, uBuff, dwBuffLen, uToken);
	LocalMemoryFree(uBuff);
	return(dwWCursor);
}

int ReplyPush(DWORD dwOption, LPVOID vBuff, DWORD dwBuffLen, wchar_t *uToken) {
	while (bReplyLock == TRUE || dwWCursor >= MAX_REPLY || bReplyStatus == FALSE)
		Sleep(2500);
	
	Reply[dwWCursor].dwOption = dwOption;
	Reply[dwWCursor].dwBuffLen = dwBuffLen;
	Reply[dwWCursor].vBuff = MemoryAlloc(dwBuffLen);
	Reply[dwWCursor].uToken = MemoryAlloc(lstrlenW(uToken));
	Reply[dwWCursor].bStatus = TRUE;

	RtlCopyMemory(Reply[dwWCursor].vBuff, vBuff, dwBuffLen);
	lstrcpynW(Reply[dwWCursor].uToken, uToken, lstrlenW(uToken));

	return(dwWCursor++);
}



int ReplyPop(LPVOID vBuff, PDWORD dwBuffLen, wchar_t *uToken) {
	int dwOption;

	while (bReplyStatus == FALSE) {}

	if (dwRCursor == dwWCursor)
		return(ReplyClean());
	

	if (Reply[dwRCursor].bStatus == TRUE) {
		dwOption = Reply[dwRCursor].dwOption;
		vBuff = MemoryAlloc(Reply[dwRCursor].dwBuffLen);
		uToken = MemoryAlloc(lstrlenW(Reply[dwRCursor].uToken));
		RtlCopyMemory(vBuff, Reply[dwRCursor].vBuff, Reply[dwRCursor].dwBuffLen);
		if (Reply[dwRCursor].uToken) {
			if (lstrlenW(Reply[dwRCursor].uToken) > 1)
				lstrcpynW(uToken, Reply[dwRCursor].uToken, lstrlenW(Reply[dwRCursor].uToken));
		}

	}

	dwRCursor++;
	return(dwOption);
}


int ReplyClean(VOID) {
	while (bReplyLock == TRUE)
		Sleep(2500);
	
	bReplyLock = TRUE;

	do {
		if (Reply[dwWCursor].bStatus == TRUE) {
			if (Reply[dwWCursor].uToken)
				MemoryFree(Reply[dwWCursor].uToken);
			if (Reply[dwWCursor].vBuff)
				MemoryFree(Reply[dwWCursor].vBuff);
		}

		Reply[dwWCursor].dwBuffLen	= 0;
		Reply[dwWCursor].dwOption	= 0;
		Reply[dwWCursor].bStatus		= FALSE;
		Reply[dwWCursor].vBuff		= NULL;
		Reply[dwWCursor].uToken		= NULL;

	} while (dwWCursor--);

	dwWCursor = dwRCursor = 0;
	bReplyLock = FALSE;
	return(-1);
}


BOOL ReplyLock(VOID)		{	bReplyLock = TRUE;	}
BOOL ReplyUnLock(VOID)	{	bReplyLock = FALSE;  }
