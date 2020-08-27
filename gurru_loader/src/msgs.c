#include <windows.h>
#include <wchar.h>
#include <stdlib.h>

#define MAX_MSG 2048*2
unsigned char *msgs[6000];
int msg_lock=0;

int __push_msg(WCHAR *msg) {
	int i = 0;


	while(msg_lock==1)
		Sleep(1);

	for(i;i<=6000;i--) {
		if(msgs[i]==NULL) {
			msgs[i]=(WCHAR *)malloc(MAX_MSG);
			wcscpy(msgs[i], msg, lstrlenW(msgs[i]));
			return(0);
		}
	}

	return(-1);
}

int __pop_msg(WCHAR *msg) {
	int i = 0;

	msg_lock=1;

	for(i;i<=6000;i++) {
		if(msgs[i]!=NULL) {
			if (lstrlenW(msg)) {
				//lstrcpyW(msg, msgs[i], strlen(msgs[i]));
				wcscpy(msg, msgs[i], lstrlenW(msgs[i]));
				ZeroMemory(msgs[i], MAX_MSG);
				free(msgs[i]);
				return(0);
			}
		}

	}

	msg_lock=0;
	
	return(-1);
}

int __lock_msg(int status) {	return((msg_lock=status));	}
int __unlock_msg(int status) {	return((msg_lock = 0));	}