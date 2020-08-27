#ifndef H_HTTP
#define H_HTTP

/*
	Simple HTTP/S implementation with proxy available
	Using wininet.dll ( InternetOpen/Connect, HTTPRequest ).
*/


/*int __http_init();
int __http_restart();

int __http_send(char *payload);
char *__http_get();

int __http_end();
*/


int __http_init();
int __http_restart();
int __http_send(int opt, char *data, char *token);
int __http_end();

#endif
