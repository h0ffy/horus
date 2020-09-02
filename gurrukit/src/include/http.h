#ifndef H_HTTP
#define H_HTTP
#include <wininet.h>
#ifdef __cplusplus
extern "C" {
#endif


	#define	DEFAULT_HTTP_FLAGS		INTERNET_FLAG_IGNORE_CERT_CN_INVALID	|	INTERNET_FLAG_IGNORE_CERT_DATE_INVALID | INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |\
									INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS	|	INTERNET_FLAG_NO_AUTH	|	INTERNET_FLAG_NO_CACHE_WRITE	|	INTERNET_FLAG_NO_UI |\
									INTERNET_FLAG_PRAGMA_NOCACHE |	INTERNET_FLAG_RELOAD  

	#define CONNECT_HTTP_FLAGS		INTERNET_FLAG_ASYNC		|	INTERNET_FLAG_DONT_CACHE	|	INTERNET_FLAG_HYPERLINK	|	INTERNET_FLAG_NO_AUTO_REDIRECT	|\
									INTERNET_NO_CALLBACK
	
	#define REQUEST_HTTP_FLAGS		INTERNET_FLAG_HYPERLINK	|	INTERNET_FLAG_PRAGMA_NOCACHE |\
									INTERNET_FLAG_NO_AUTH	|	INTERNET_FLAG_NO_CACHE_WRITE	|	INTERNET_FLAG_NO_AUTO_REDIRECT




	typedef struct _CCHTTP_STRUCT {
		wchar_t *wURL;
		wchar_t *wHost;
		USHORT usPort;
		USHORT usMethod; // 0:POST, 1:REFERER, 2:COOKIE
		wchar_t *wUserAgent;
		wchar_t *wPath;
		HINTERNET *hInternet;
		HANDLE *hFile;
		HINTERNET *hConnect;
		HINTERNET *hRequest;
		wchar_t *wProxyUrl;
		wchar_t *wProxyUser;
		wchar_t *wProxyPass;
	}CCHTTP, *PCCHTTP;




	//int httpInit(void);
	wchar_t *httpRecv(struct _CCHTTP_STRUCT *ccInfo, wchar_t *wData);
	DWORD httpSend(PCCHTTP ccInfo, wchar_t *wData);
	DWORD httpInit(PCCHTTP ccInfo);
	DWORD httpProxyConfig(PCCHTTP ccInfo);

#ifdef __cplusplus
}
#endif
#endif

