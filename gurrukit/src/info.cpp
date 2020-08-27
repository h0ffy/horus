#include <windows.h>
#include <winternl.h>
#include <psapi.h>
#include "include/gurrukit.h"
#include "include/memory.h"
#include "include/info.h"

int cinfo(lp_info lpInfo) {
	info inf = info::info();
	//pinf = &inf;

	lstrcpynW(lpInfo->cstrComputerName, cstrComputerName, 512);
	lstrcpynW(lpInfo->cstrUserName, cstrUserName, 256);
	return(0);

}



/*
int info::b(void) {
	return(0);
}
*/
info::info(void) {
	this->strUserName = (wchar_t *)::MemoryAlloc(2048);
	this->strComputerName = (wchar_t *)::MemoryAlloc(2048);
	
	this->RetreiveUserName();
	this->GetCompName();
	cstrUserName = this->strUserName;
	cstrComputerName = this->strComputerName;
}

info::~info(void) {
	::MemoryFree(this->strUserName);
	::MemoryFree(this->strComputerName);
}

BOOL info::RetreiveUserName() {
	DWORD dwBufferLen;

	try {

		if (GetUserNameW(this->strUserName, &dwBufferLen) != TRUE) {
			if (dwBufferLen <= 2048)
				dwBufferLen = 2048 * 2;

			this->strUserName = (wchar_t *)::MemoryReAlloc(this->strUserName, dwBufferLen);

			if (GetUserNameW(this->strUserName, &dwBufferLen) != TRUE) {
				lstrcpynW(this->strUserName, L"Unknow",2048);
				return(FALSE);
			}
		}
	}
	catch(int dwError) {
		this->strUserName = (wchar_t *)NULL;
		this->strUserName = (wchar_t *)::MemoryAlloc(2048);
		lstrcpynW(this->strUserName, L"Unknow",2048);
		return(FALSE);
	}
	return(FALSE);
}


BOOL info::GetCompName(void) {
	DWORD dwSize, dwMethod = 0;

	try {

		for (dwMethod = 0; dwMethod < 8; dwMethod++) {
			if (GetComputerNameExW((COMPUTER_NAME_FORMAT)dwMethod, this->strComputerName, &dwSize))
				return(TRUE);
			else {
				if (dwSize > 2048) {
					this->strComputerName = (wchar_t *)::MemoryReAlloc(this->strComputerName, dwSize);
				}
			}
		}
		lstrcpynW(this->strComputerName, L"Unknow", 2048);
		return(FALSE);

	}
	catch(int dwError) {
		this->strComputerName = (wchar_t *)NULL;
		this->strComputerName = (wchar_t *)::MemoryAlloc(2048);
		lstrcpynW(this->strComputerName, L"Unknow", 2048);
		return(FALSE);
	}
	return(FALSE);
}
