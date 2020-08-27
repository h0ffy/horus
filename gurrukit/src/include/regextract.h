#ifndef H_REGEXTRACT
#define H_REGEXTRACT
#ifdef __cplusplus
extern "C" {
#endif

	#define MAX_EXTRACT_COUNT 10

	typedef struct _RegExpressions {
			const DWORD		dwID;
			const char		*lpRegExpression;
			const DWORD		dwNumberOfItems;
			const BOOL		bCaseSensitive;
	}RegExpression, *lpRegExpression;
	

	typedef struct _RegExtractStruct {
			DWORD	dwID;
			wchar_t *uItems[MAX_EXTRACT_COUNT];
			DWORD	dwCount;
			BOOL	bMatch;
	} RegExtractStruct, *lpRegExtractStruct;

	typedef RegExtractStruct _regextract;
	typedef lpRegExtractStruct _pregextract;


	BOOL RegExtractA(lpRegExtractStruct lpExtract, const char *lpBuff);
	BOOL RegExtractW(lpRegExtractStruct lpExtract, const wchar_t *uBuff);






#ifdef __cplusplus
}
#endif
#endif
