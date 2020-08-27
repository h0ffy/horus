#ifndef H_CRYPTO
#define H_CRYPTO
#ifdef __cplusplus
extern "C" {
#endif
	

	typedef struct _RC4_BOX {
		BYTE data[256];
		int val1;
		int val2;
	}RC4_BOX, *PRC4_BOX;

	PRC4_BOX CryptoRC4Init(BYTE *Key, DWORD dwKeyLen);


	wchar_t *CryptoRC4StringW(wchar_t *uBuff, DWORD dwBuffLen, wchar_t *uPassword);



#ifdef __cplusplus
}
#endif
#endif