
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

int main() {
	char str[MAX];
	while(1){
		printf("12161104_shell$" );
		fgets(str, MAX, stdin);
		if(strcmp(str, "quit") == 0){
			printf("myshell developed by \"박범근(12161104)\"\n");
			break;
		}
		else{
		printf("%s", str);
		}

	}
}

