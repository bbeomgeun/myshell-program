
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

int main() {
	char str[MAX];
	while(1){
		printf("12161104_shell$" );
		fgets(str, MAX-1, stdin); // fgets는 끝에 null 저장(한칸비워야함)
		
		// 문자열 토큰화
		char delimeter[] = " ";
		char parsing[3][16];
		char *result;
		int i = 0;

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
			result = strtok(str, delimeter);

			while(result != NULL){
				strcpy(parsing[i++], result);
				result = strtok(NULL, delimeter);
			}		
			for(int i = 0 ; i < 3 ; i++)
				printf("%s", parsing[i]);
		}

		
		

	}
}

