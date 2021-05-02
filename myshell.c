
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 100

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

		if(strncmp(str, "quit", 4) == 0){
			printf("myshell developed by \"박범근(12161104)\"\n");
			break;
		}
		else if(strncmp(str, "history", 7) == 0){
			printf("history print\n");
		}
		else if(strncmp(str, "help", 4) == 0) {
			printf("DESCRIPTION~~\n");
		}
		else{
			int count = strParsing(parsing, str, " ");
			
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

