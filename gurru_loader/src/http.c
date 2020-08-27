#include <windows.h>
#include <tchar.h>
#include <wininet.h>
#include "include/config.h"
#include "include/http.h"

HINTERNET hInet;
HINTERNET hConnect;

int __http_init() {
	hInet = InternetOpenA(HTTP_AGENT, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_ASYNC);
	
	if(hInet==NULL)
		return -1;


	hConnect = InternetConnectA(hInet, HTTP_URL, HTTP_PORT, 0, 0, INTERNET_SERVICE_HTTP, 
			INTERNET_FLAG_IGNORE_CERT_DATE_INVALID	|
			INTERNET_FLAG_IGNORE_CERT_CN_INVALID	|
			INTERNET_FLAG_KEEP_CONNECTION		|
			INTERNET_FLAG_PRAGMA_NOCACHE		|
			INTERNET_FLAG_RESYNCHRONIZE,
			0);

	if(hConnect == NULL)
		return -1;
	
	

	return 0;	
}


int __http_restart() {

	InternetCloseHandle(hConnect);
	
        hConnect = InternetConnectA(hInet, HTTP_URL, HTTP_PORT, 0, 0, INTERNET_SERVICE_HTTP,
                        INTERNET_FLAG_IGNORE_CERT_DATE_INVALID  |
                        INTERNET_FLAG_IGNORE_CERT_CN_INVALID    |
                        INTERNET_FLAG_KEEP_CONNECTION           |
                        INTERNET_FLAG_PRAGMA_NOCACHE            |
                        INTERNET_FLAG_RESYNCHRONIZE,
                        0);

        if(hConnect == NULL)
                return -1;


	return 0;
}


int __http_send(int opt, char *data, char *token) {
	char *final = (char *)malloc(HTTP_MAX_PAY);
	return(0);
}


int __http_end() {
	int ret = 0;
	if(InternetCloseHandle(hConnect)==TRUE) ret=1;
	if(InternetCloseHandle(hInet)==TRUE) ret=1;
	return(0);
}
