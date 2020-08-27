#include <windows.h>
#include <winternl.h>
#include "include/sys.h"

extern unsigned long getsystem_imagebase(void);

unsigned long sysGetImageBase(void) {
/*		__asm("movl %fs:0x30,%eax");
		__asm("movl 0x08(%eax), %eax");
		__asm("movl %eax, %eax");
		__asm("movl %%eax, %0" : "=r" (uret)); 
*/
	return(getsystem_imagebase());
}


