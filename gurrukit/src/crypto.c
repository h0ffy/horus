#include <windows.h>
#include "include/gurrukit.h"
#include "include/memory.h"
#include "include/misc.h"
#include "include/crypto.h"


wchar_t *CryptoGurruStringW(wchar_t *uString) {




}


LPVOID CryptoRC4DataCrypt(LPVOID Buff, DWORD dwBuffLen, PUCHAR iPassword, DWORD dwPasswordLen, PDWORD dwReaded) {
	LPVOID CryptBuff = MemoryAlloc(dwBuffLen);
	BYTE Key[256] = { 0 };
	PRC4_BOX box;
	int i = dwPasswordLen;

	if (dwBuffLen == 0 || dwPasswordLen == 0)
		return((wchar_t *)NULL);

	for (i = 0; i < dwPasswordLen; i++) {
		Key[i] = (BYTE)iPassword[i];
	}

	box = CryptoRC4Init(Key, dwPasswordLen);
	CryptoRC4Crypt(box, Buff, CryptBuff, dwBuffLen);
	
	dwReaded = i;

	return(CryptBuff);
}

VOID CryptoRC4End(PRC4_BOX *box) {
	MemoryFree(box);
}

PRC4_BOX CryptoRC4Init(BYTE *Key, DWORD dwKeyLen) {
	RC4_BOX *box = NULL;
	int val2 = 0, i = 0;

	if ((box = MemoryAlloc((sizeof(RC4_BOX)))) == NULL)
		return((PRC4_BOX)NULL);

	box->val2 = 0;

	for (i = 0; i < 256; i++)
		box->data[i] = i;

	i = 0;
	for (val2 = 0; i < 256; i++) {
		val2 = (val2 + box->data[i] + Key[i % dwKeyLen]) & 0xff;
		swap(box->data, i, val2);
	}


	return(box);

}

BYTE CryptoRC4GenKey(PRC4_BOX box) {
	box->val1 = (box->val1 + 1) & 0xff;
	box->val2 = (box->val2 + box->data[box->val1]) & 0xff;
	swap(box->data, box->val1, box->val2);

	return(box->data[(box->data[box->val1] + box->data[box->val2]) & 0xff]);
}

DWORD CryptoRC4Crypt(PRC4_BOX box, BYTE *inData, BYTE *outData, DWORD dwBuffLen) {
	int i;
	BYTE clcKey;

	for (i = 0; i < dwBuffLen; i++) {
		clcKey = CryptoRC4GenKey(box);
		outData[i] = inData[i] ^ clcKey;
	}

	return(i);
}