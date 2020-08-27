#ifndef H_HOOKING
#define H_HOOKING
#ifdef __cplusplus
extern "C" {
#endif
#include "hook.h"

	int HookingDefault(void);
	int HookIAT(CHAR *dllName, CHAR *funcName, LPVOID *hkFunc);
	DWORD HookEAT(HMODULE hMod, CHAR *szFuncName, LPVOID hkFunc);
	//DWORD HookEAT(HMODULE mod, CHAR * FN, VOID* HA, VOID** OA);

	typedef struct _HOOKS {
		const char *iDLLName;
		const char *iAPIName;
		/*
		DWORD		dwApiHash;
		BYTE		byApiKey
		*/
		void		*hkFunc;
		void		**orgFunc;
		BOOL		IAT_METHOD;
		BOOL		EAT_METHOD;
		BOOL		PATCH_METHOD;
		BOOL		PAGE_METHOD;
	}HOOKS, *LPHOOKS;

	DWORD HookVEH(PDWORD pExceptionPoint, PVECTORED_EXCEPTION_HANDLER pvExceptionCallBack); // PDWORD pExceptionPoint, PVECTORED_EXCEPTION_HANDLER pExceptionCallBack, PDWORD hkFunc);
	DWORD WINAPI HookVEHCallBack(EXCEPTION_POINTERS *pExceptionInfo);

#ifdef __cplusplus
}
#endif
#endif
