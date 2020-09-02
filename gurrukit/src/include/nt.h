#ifndef H_NTOS
#define H_NTOS
#ifdef __cplusplus
extern "C" {
#endif
	
	void NtLoader(void);
	
	//NTSTATUS NT_STATUS(unsigned long int val);

	#if defined(_MSC_VER)
	NTSTATUS NT_STATUS(unsigned long int val);
	typedef struct _CLIENT_ID
	{
		PVOID UniqueProcess;
		PVOID UniqueThread;
	}CLIENT_ID, *PCLIENT_ID;
	#endif

	NTSTATUS (__stdcall *_NtWriteVirtualMemory)(PVOID ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten);
	NTSTATUS (__stdcall *_NtOpenProcess)(PHANDLE hProcess, ACCESS_MASK Mask, POBJECT_ATTRIBUTES  pObjAttributes, PCLIENT_ID cID);
	NTSTATUS (__stdcall *_ZwSetInformationProcess)(void *hProcess, unsigned long ProcessInfoClass, void *ProcessInfo, unsigned long ProcessInfoLength);
	NTSTATUS (__stdcall *_NtQueryInformationProcess)(void *hProcess, PROCESSINFOCLASS ProcessInformationClass, void *ProcessInformation, unsigned long ProcessInformationLength, unsigned long *ReturnLength);
	NTSTATUS (__stdcall *_NtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass, void *SystemInformation, unsigned long SystemInformationLength, unsigned long *ReturnLength);
	NTSTATUS (__stdcall *_NtTerminateProcess)(void *hProcess, unsigned long nt_status);
	NTSTATUS (__stdcall *_NtOpenProcess)(void *hProcess, ACCESS_MASK mask, POBJECT_ATTRIBUTES  pObjAttr, PCLIENT_ID clientID);
	NTSTATUS (__stdcall *_NtWriteVirtualMemory)(void *ProcessHandle, void *BaseAddress, void *Buffer, unsigned long NumberOfBytesToWrite, unsigned long *NumberOfBytesWritten);
	NTSTATUS (__stdcall *_NtClose)(void *hHandle);
	NTSTATUS (__stdcall *_NtWaitForSingleObject)(void *hHandle, int Alertable, LONGLONG *pTimeout);
	NTSTATUS (__stdcall *_NtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass, void *SystemInformation, unsigned long SystemInformationLength, unsigned long *ReturnLength);
	NTSTATUS (__stdcall *_NtCreateFile)(void	**FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK   IoStatusBlock, PLARGE_INTEGER AllocationSize, ULONG FileAttributes, ULONG ShareAccess, unsigned long CreateDisposition, unsigned long CreateOptions, void *EaBuffer, unsigned long EaLength);
	NTSTATUS(__stdcall *_RtlCreateUserThread)(void *hProcess, PSECURITY_DESCRIPTOR SecurityDescriptor, int CreateSuspend, unsigned long StackZeroBits, unsigned long *stackReserved, unsigned long *stackCommit, void *startAddress, void *startParams, void *hThread, PCLIENT_ID clientID);
	NTSTATUS (__stdcall *_RtlAdjustPrivilege)(unsigned long Privilege, int Enable, int CurrentThread, int *Enabled);
	PIMAGE_NT_HEADERS (__stdcall *_RtlImageNtHeader)(void *memOffset);
	NTSTATUS(__stdcall *_NtOpenFile)(PHANDLE FileHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PIO_STATUS_BLOCK IoStatusBlock, ULONG SharedAccess, ULONG OpenOptions);
	NTSTATUS(__stdcall *_NtReadVirtualMemory)(HANDLE hProc, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesReaded);
	NTSTATUS (__stdcall *_NtWriteFile)(HANDLE FileHandle,HANDLE Event,PIO_APC_ROUTINE  ApcRoutine,PVOID ApcContext,PIO_STATUS_BLOCK IoStatusBlock,PVOID Buffer,ULONG Length,PLARGE_INTEGER ByteOffset,PULONG Key);
	VOID(__stdcall *_RtlInitUnicodeString)(PUNICODE_STRING DestinationString, PCWSTR SourceString);
	NTSTATUS(__stdcall *_NtQueryInformationFile)(HANDLE FileHandle, PIO_STATUS_BLOCK IoStatusBlock, PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS);

	#ifdef _WIN64
		unsigned int *find_function64(HANDLE *hDll, unsigned long dwApiHash);
		int *find_kernel64(VOID); 
		#define find_function find_function64
		#define find_kernel find_kernel64
	#else
		unsigned int *find_function32(HANDLE *hDll, unsigned long dwApiHash);
		int *find_kernel32(VOID);
		#define find_function find_function32
		#define find_kernel find_kernel32
	#endif


	typedef struct _SYSTEM_PROCESS_INFO
	{
		ULONG                   NextEntryOffset;
		ULONG                   NumberOfThreads;
		LARGE_INTEGER           Reserved[3];
		LARGE_INTEGER           CreateTime;
		LARGE_INTEGER           UserTime;
		LARGE_INTEGER           KernelTime;
		UNICODE_STRING          ImageName;
		ULONG                   BasePriority;
		HANDLE                  ProcessId;
		HANDLE                  InheritedFromProcessId;
	}SYSTEM_PROCESS_INFO, *PSYSTEM_PROCESS_INFO;


#ifdef __cplusplus
}
#endif
#endif
