
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100

void help_description(){
	printf("<DESCRIPTION\n");
	printf("csh is a command language interpreter incorporating a history mechanism (see Sx History substitutions ) , job control facilities (see Sx Jobs ) , interactive file name and user name completion (see Sx File name completion ) , and a C-like syntax. It is used both as an interactive login shell and a shell script command processor\n");
	return ;
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

	while(1){
		printf("12161104_shell$" );
		fgets(str, MAX-1, stdin); // fgets는 끝에 null 저장(한칸비워야함)
		str[strlen(str)-1]='\0';

		char * delimeter = " ";
		char * parsing[MAX];

		int count = strParsing(parsing, str, " ");

		if(strcmp(parsing[0], "quit") == 0){
			printf("myshell developed by \"박범근(12161104)\"\n");
			break;
		}
		else if(strcmp(parsing[0], "history") == 0){
			printf("history print\n");
		}
		else if(strcmp(parsing[0], "help") == 0) {
			help_description();
		}
		else{
						
			pid_t pid;

			switch(pid = fork()){
				case -1 :
					printf("fork failed");
					break;
				case 0:
					execvp (parsing[0], parsing);
					break;
				default:
					wait((int *)0);
					printf("ls ompleted\n");
			}
		}	
	}
}

