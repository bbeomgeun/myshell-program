
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
	printf("csh is a command language interpreter incorporating a history mechanism (see Sx History substitutions ) , job control facilities (see Sx Jobs ) , interactive file name and user name completion (see Sx File name completion ) , and a C-like syntax. It is used both as an interactive login shell and a shell script command processor\n
		break [n]                                                   printf [-v var] format [arguments]
		 builtin [shell-builtin [arg ...]]                           pushd [-n] [+N | -N | dir]
		  caller [expr]                                               pwd [-LP]
		   case WORD in [PATTERN [| PATTERN]...) COMMANDS ;;]... esa>  read [-ers] [-a array] [-d delim] [-i text] [-n nchars] >
		 cd [-L|[-P [-e]] [-@]] [dir]                                readarray [-d delim] [-n count] [-O origin] [-s count] [>
		  command [-pVv] command [arg ...]                            readonly [-aAf] [name[=value] ...] or readonly -p
		   compgen [-abcdefgjksuv] [-o option] [-A action] [-G globp>  return [n]
		    complete [-abcdefgjksuv] [-pr] [-DEI] [-o option] [-A act>  select NAME [in WORDS ... ;] do COMMANDS; done
		     compopt [-o|+o option] [-DEI] [name ...]                    set [-abefhkmnptuvxBCHP] [-o option-name] [--] [arg ...]
		      continue [n]                                                shift [n]
		       coproc [NAME] command [redirections]                        shopt [-pqsu] [-o] [optname ...]
		        declare [-aAfFgilnrtux] [-p] [name[=value] ...]             source filename [arguments]
			 dirs [-clpv] [+N] [-N]                                      suspend [-f]
			  disown [-h] [-ar] [jobspec ... | pid ...]                   test [expr]
			   echo [-neE] [arg ...]                                       time [-p] pipeline
			    enable [-a] [-dnps] [-f filename] [name ...]                times
			     eval [arg ...]                                              trap [-lp] [[arg] signal_spec ...]
			      exec [-cl] [-a name] [command [arguments ...]] [redirecti>  true
			       exit [n]                                                    type [-afptP] name [name ...]
			        export [-fn] [name[=value] ...] or export -p                typeset [-aAfFgilnrtux] [-p] name[=value] ...
				 false                                                       ulimit [-SHabcdefiklmnpqrstuvxPT] [limit]
				  fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [c>  umask [-p] [-S] [mode]
				   fg [job_spec]                                               unalias [-a] name [name ...]
				    for NAME [in WORDS ... ] ; do COMMANDS; done                unset [-f] [-v] [-n] [name ...]
					     for (( exp1; exp2; exp3 )); do COMMANDS; done               until COMMANDS; do COMMANDS; done
						      function name { COMMANDS ; } or name () { COMMANDS ; }      variables - Names and meanings of some shell variables
							       getopts optstring name [arg]                                wait [-fn] [id ...]
							        hash [-lr] [-p pathname] [-dt] [name ...]                   while COMMANDS; do COMMANDS; done
								 help [-dms] [pattern ...]                                   { COMMANDS ; }");
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
	int status;
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
			pid_t pid = fork();
			if(pid == -1){
				printf("fork failed");	
			}
			else if(pid == 0){
				execvp(parsing[0], parsing);
				exit(0);
			}
			else{
				if(!backgroundFlag){
					printf("대기");
					//pid = wait(&status);
					wait(NULL);
					printf("부모실행");
				}
				else{
					waitpid(-1, &status, WNOHANG);
					//pid = wait(&status);
					printf("백그라운드");
					
				}
			}
		}
	}
}

