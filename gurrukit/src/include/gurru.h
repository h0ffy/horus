#ifndef H_GURRU
#define H_GURRU
#ifdef __cplusplus
extern "C" {
#endif
	BOOL isMutex;
	BOOL ImageBase;
	
	ULONG_PTR gurruImageBase();
	BOOL gurruIsMutex();
	int gurruInit(BOOL isMut);





#ifdef __cplusplus
}
#endif
#endif
