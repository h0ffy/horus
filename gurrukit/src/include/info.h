#ifndef H_INFO
#define H_INFO



/*
typedef struct _vxME_INFO {
	int privileges;
	wchar_t *name;
	wchar_t *path;
	wchar_t *botid;
}ME_INFO, *PME_INFO;


typedef struct _vxSYS_INFO {
	wchar_t *strOsVersion;
	wchar_t *PCname;
	wchar_t *UserName;
	wchar_t *Domain;
	wchar_t *strCPUID;
	wchar_t *strDrivesId[25];
	wchar_t *strDrivesPath[25]; // example: "C:\", "D:\" 
	wchar_t *strSysPath;
	wchar_t *strTempPath;
}vxSYS_INFO, *PvxSYS_INFO;

ME_INFO stME;
vxSYS_INFO stSysInfo;

*/

#ifdef __cplusplus


class info {
	private:
		int RetreiveUserName();
		int GetCompName(void);

	public:
		info();
		~info();
		wchar_t *strUserName;
		wchar_t *strComputerName;

};
extern "C" {
	typedef struct _INFO_STRUCT {
		wchar_t *cstrUserName;
		wchar_t *cstrComputerName;
	}st_info, *lp_info;

	int cinfo(lp_info lpInfo);
	wchar_t *cstrUserName;
	wchar_t *cstrComputerName;
};
#else
	typedef struct _INFO_STRUCT {
		wchar_t *cstrUserName;
		wchar_t *cstrComputerName;		
	}st_info, *lp_info;

	int cinfo(lp_info lpInfo);

	wchar_t *cstrUserName;
	wchar_t *cstrComputerName;
#endif

/*
class info {
	public:
		info(void);
		~info(void);
		int b(void);
};

	*/
	//	int b(void);
	

#endif