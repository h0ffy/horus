#ifndef H_PAYLOADS
#define H_PAYLOADS
#ifdef __cplusplus
extern "C" {
#endif

static unsigned char x64gate_start[] =	"\x6a\x33"					// pushq 0x33
										"\xe8\x00\x00\x00\x00"		// call $+5
										"\x83\x04\x24\x05"			// add dword [esp], 5
										"\xcb";						// retf


static unsigned char x64gate_end[] =	"\xe8\x00\x00\x00"						// call $+5
										"\xc7\x44\x24\x04\x23\x00\x00\x00"		// mov dword [rsp+4], 0x23
										"\x83\x04\x24\x0D"						// add dword [rsp]
										"\xCB";									// retf




#ifdef __cplusplus
}
#endif
#endif