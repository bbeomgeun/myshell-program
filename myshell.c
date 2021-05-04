
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100

void help_description(){
	printf("<DESCRIPTION>\n");
	printf("csh is a command language interpreter incorporating a history mechanism (see Sx History substitutions ) , job control facilities (see Sx Jobs ) , interactive file name and user name completion (see Sx File name completion ) , and a C-like syntax. It is used both as an interactive login shell and a shell script command processor\n");
	return ;
}

void history(char * list[], int cnt){
	int now = cnt % 10;
	if(now == 0)
		now = 10;
	int real = cnt-9;
	
	printf("----history 10----\n");
 
	if(cnt <= 10){
		for(int i = 1 ; i <= now ; i++){
			printf("%d     %s\n",i, list[i]);
		}
	}
	else{
		for(int i = now+1 ; i <= 10 ; i++){
			printf("%d     %s\n",real++, list[i]);
		}	
		for(int i = 1 ; i <= now ; i++){
			printf("%d     %s\n",real++, list[i]);
		}
	}
}

int strParsing(char * list[], char * command, const char * delimeter){
	int cnt = 0;
	char * result;
	result = strtok(command, delimeter);
	while(result != NULL){
		list[cnt++] = result;
		result = strtok(NULL, delimeter);
	}
	list[cnt] = NULL;
	return cnt;
}

int main() {
	char str[MAX];
	char * history_list[11];
	char * hisstr;
	int his_cnt = 1;
	int backgroundFlag;
	
	while(1){
		printf("12161104_shell$" );
		fgets(str, MAX-1, stdin); // fgets는 끝에 null 저장(한칸비워야함)
	
		// 입력값 history에 저장하기
		hisstr = (char*)malloc(sizeof(char*)*(strlen(str)+1));
		strcpy(hisstr, str);
		int his_now = his_cnt % 10;
		if(his_now == 0)
			his_now = 10;
		if(his_cnt > 10)
			free(history_list[his_now]);
		history_list[his_now] = hisstr;
		his_cnt++;

		// 백그라운드 찾기
		backgroundFlag = false;
		if (str[strlen(str)-2] == '&'){
			str[strlen(str)-2]='\0';
			backgroundFlag = true;
		}
		else
			str[strlen(str)-1] = '\0';
	
		// 문자열 파싱
		char * delimeter = " ";
		char * parsing[MAX];

		int count = strParsing(parsing, str, " ");

		if(strcmp(parsing[0], "quit") == 0){
			printf("myshell developed by \"박범근(12161104)\"\n");
			break;
		}
		else if(strcmp(parsing[0], "history") == 0){
			history(history_list, his_cnt-1);
		}
		else if(strcmp(parsing[0], "help") == 0) {
			help_description();
		}
		else{	
			int status;			
			pid_t pid = fork();
			if(pid == -1){
				printf("fork failed");	
			}
			else if(pid == 0){
				execvp(parsing[0], parsing);
			}
			else{
				if(!backgroundFlag){
					printf("대기");
					pid = wait(&status);
					printf("부모실행");
				}
				else{
					waitpid(pid, &status, WNOHANG);
					printf("백그라운드");
				}
			}
		}
	}
}

