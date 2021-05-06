#include "myshell.h"

void cmd_help() {
	printf("<DESCRIPTION>\n");
	printf("csh is a command language interpreter incorporating a history mechanism (see Sx History substitutions ) , job control facilities (see Sx Jobs ) , interactive file name and user name completion (see Sx File name completion ) , and a C-like syntax. It is used both as an interactive login shell and a shell script command processor\n");
	return;
}

void cmd_history(char* list[], int cnt) {
	int now = cnt % 10;
	if (now == 0)
		now = 10;
	int real = cnt - 9;

	printf("----history 10----\n");

	if (cnt <= 10) {
		for (int i = 1; i <= now; i++) {
			printf("%d     %s\n", i, list[i]);
		}
	}
	else {
		for (int i = now + 1; i <= 10; i++) {
			printf("%d     %s\n", real++, list[i]);
		}
		for (int i = 1; i <= now; i++) {
			printf("%d     %s\n", real++, list[i]);
		}
	}
}

void insertHistory(char* str, int hiscnt) {
	char* hisstr = (char*)malloc(sizeof(char*) * (strlen(str) + 1));
	strcpy(hisstr, str);
	int his_now = hiscnt % 10;
	if (his_now == 0)
		his_now = 10;
	if (hiscnt > 10)
		free(history_list[his_now]);
	history_list[his_now] = hisstr;
}

int strParsing(char* list[], char* command, const char* delimeter) {

	if (command[strlen(command) - 2] == '&') {
		command[strlen(command) - 2] = '\0';
		backgroundFlag = true;
	}
	else {
		command[strlen(command) - 1] = '\0';
		backgroundFlag = false;
	}

	int cnt = 0;	
	char* result;		
	result = strtok(command, delimeter);
		
	while (result != NULL) {

		list[cnt++] = result;
		result = strtok(NULL, delimeter);
	
	}

	list[cnt] = NULL;
	return cnt;
}

void backgroundExecute(char* command[]) {
	pid_t pid = fork();
	if (pid == -1) {
		printf("fork failed");
	}

	else if (pid == 0) { 
		execvp(command[0], command);
		exit(0);
	}
}

void foregroundExecute(char* command[]) {
	
	pid_t pid = fork();
	if (pid == -1) {
		printf("fork failed");
	}
	else if (pid == 0) { // child
		execvp(command[0], command);
		exit(0);

	}
	else { // parent
		wait(0);
	}
}
