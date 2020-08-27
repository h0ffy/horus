#ifndef N_NTAPIs
#define N_NTAPIs
#include <winternl.h>


struct st_gurrucalls {
	int gurrucall;
	void *(*func)();
}gurrus;



NTSTATUS (*l_NtQueryInformationThread)(	HANDLE          ThreadHandle,
						THREADINFOCLASS ThreadInformationClass,
						PVOID           ThreadInformation,
						ULONG           ThreadInformationLength,
						PULONG          ReturnLength);


#endif
