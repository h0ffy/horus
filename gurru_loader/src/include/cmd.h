#ifndef H_CMD
#define H_CMD

struct cmd_struct {
	char *cmd;
	char *args[25];
	char *token;
};

typedef struct cmd_struct cmd_data;

struct command {
	char *cmd;
	int (*func)(cmd_data *data);
};


int cc_test(cmd_data *data);
int command(WCHAR *raw);

#endif