#include "myshell.h"

int main() {
	int his_cnt = 1;
	while (1) {
		printf("12161104_shell$");
		fgets(str, MAX_CMD - 1, stdin);
		
		//manage zombie process
		waitpid(-1, NULL, WNOHANG);

		insertHistory(str, his_cnt);
		his_cnt++;

		strParsing(parsing, str, " ");
	
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
		else {
			if(backgroundFlag) {
				backgroundExecute(parsing);
			}
			else if (!backgroundFlag) {
				foregroundExecute(parsing);
			}
		}
	}
	return 0;
}

