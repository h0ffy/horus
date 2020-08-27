#include <windows.h>
#include <winternl.h>
#include <intrin.h>
#include "include/gurru.h"
#include "include/memory.h"
#include "include/misc.h"

static int m_rand = 0x42414C4A;


#ifdef _WIN64
	isGurru64 = TRUE;
#else
	isGurru64 = FALSE;
#endif

extern ULONG nGetCPUID(void);
extern BYTE random_byte(ULONG val1, UINT val2, UINT val3);
extern void GetCPUID(wchar_t *wCPUID);
extern BOOL iswOw64(void);


unsigned char rand_byte(void) {
	unsigned char  bByte;
	DWORD dwByte = random_byte(nGetCPUID(), 255, 0x796e654a);

	bByte = (unsigned char)dwByte & 0xFFFFFF00;
	return(bByte);
}


void swap(BYTE *data, DWORD val1, DWORD val2) {
	BYTE tmp;

	tmp = data[val1];
	data[val1] = data[val2];
	data[val2] = tmp;

}
/*
BYTE random_byte2(void) {
	int max = 255;
	BYTE bRet = (BYTE)0;
	int padd = 100711433;

	if (m_rand == 0x42414C4A)
		m_rand = nGetCPUID();

	#ifdef _WIN64
	__asm {
			cld
			mov rdx, rax
			rdtsc
			adc rax, rdx
			
	}
	#else
	__asm {
			cld
			lea edx, max
			rdtsc
			adc eax, edx
			adc eax, m_rand
			mul padd
			adc eax, edx
			mov m_rand, eax
			mul max
			mov eax, eax
			mov bRet, al
	}
	#endif
	return(bRet);
}
*/
/*
unsigned long nGetCPUID(void)
{
	unsigned int cpuinfo[4];
	DWORD dwRet;

	__asm
	{
			lea edi, cpuinfo
			mov eax, 1
			cpuid
			mov dword ptr[edi + 0], eax
			mov dword ptr[edi + 4], ebx
			mov dword ptr[edi + 8], ecx
			mov dword ptr[edi + 12], edx
			mov esi, eax
			xor eax, eax
			add eax, esi
			add eax, ebx
			add eax, ecx
			add eax, edx
			mov dwRet, eax
	}

	return(dwRet);
}

*/
int GetCPUIDUString(wchar_t *wCPUID)
{
	unsigned int cpuinfo[4];
	/*
	__asm
	{
			lea edi, cpuinfo
			xor eax, eax
			mov eax, 1
			cpuid
			mov dword ptr[edi + 0], eax
			mov dword ptr[edi + 4], ebx
			mov dword ptr[edi + 8], ecx
			mov dword ptr[edi + 12], edx
	}
	*/
	//wCPUID = (wchar_t *)MemoryAlloc(1024);
	wsprintf(wCPUID, L"%d%d%d%d", cpuinfo[0], cpuinfo[1], cpuinfo[2], cpuinfo[3]);
	
	return 0;
}