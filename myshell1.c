#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_CMD 100

char str[MAX_CMD];
char* history_list[11];
char* delimeter = " ";
char* parsing[MAX_CMD];
int his_cnt = 1;
int backgroundFlag;

void cmd_help();
void cmd_history(char* list[], int cnt);
int cmd_cd(char* str);
void insertHistory(char* str);
int strParsing(char* list[], char* command, const char* delimeter);
void backgroundExecute(char* command[]);
void foregroundExecute(char* command[]);

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

int cmd_cd(char* str) {
	if (chdir(str) == -1)
		perror(str);
}

void insertHistory(char* str) {
	char* hisstr = (char*)malloc(sizeof(char*) * (strlen(str) + 1));
	strcpy(hisstr, str);
	int his_now = his_cnt % 10;
	if (his_now == 0)
		his_now = 10;
	if (his_cnt > 10)
		free(history_list[his_now]);
	history_list[his_now] = hisstr;
	his_cnt++;
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
	else if (pid == 0) { // 부모는 무시
		execvp(command[0], command);
		exit(0);
	}
}

void foregroundExecute(char* command[]) {
	pid_t pid = fork();
	if (pid == -1) {
		printf("fork failed");
	}
	else if (pid == 0) { // 부모는 무시
		execvp(command[0], command);
		exit(0);
	}
	else {
	wait(0);
	//sleep(1);
	}
}

int main() {

	while (1) {
		printf("12161104_shell$");
		fgets(str, MAX_CMD - 1, stdin); // fgets는 끝에 null 저장(한칸비워야함)
		
		//zombie 프로세스 받아주기
		waitpid(-1, NULL, WNOHANG);

		// 입력값 history에 저장하기
		insertHistory(str);

		// 문자열 파싱
		int count = strParsing(parsing, str, " ");
	
		if (strcmp(parsing[0], "quit") == 0) {
			printf("myshell developed by \"박범근(12161104)\"\n");
 			exit(0);
		}
		else if (strcmp(parsing[0], "history") == 0) {
			cmd_history(history_list, his_cnt - 1);
		}
		else if (strcmp(parsing[0], "help") == 0) {
			cmd_help();
		}
		else if (strcmp(parsing[0], "cd") == 0) {
			cmd_cd(parsing[1]);
		}
		else {
			if(backgroundFlag) {
				backgroundExecute(parsing);
				printf("백그라운드");
			}
			else if (!backgroundFlag) {
				foregroundExecute(parsing);
				printf("부모대기");
			}
		}
	}
}

