#ifndef H_GURRUKIT_DLL
#define H_GURRUKIT_DLL


#define DLL_QUERY_HMODULE 0x06

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif



#ifdef __cplusplus
	extern "C" {
#endif

	#ifndef _MSC_VER
		#ifdef BUILDING_GURRUKIT_DLL
			#define GURRUDLL __declspec(export)
		#else
			#define GURRUDLL __declspec(import)
		#endif
	#else
			#define GURRUDLL __declspec(dllexport)
	#endif


	GURRUDLL BOOL __stdcall runBot(void);
	//GURRUDLL VOID WINAPI ReflectiveLoader(void *lpParams, void *lpLibraryAddress, DWORD dwFunctionHash, void *lpUserData, DWORD nUserdataLen); 
	





#ifdef __cplusplus
}
#endif
#endif
