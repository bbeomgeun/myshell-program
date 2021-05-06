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
char* parsing[MAX_CMD];
int backgroundFlag;

void cmd_help();
void cmd_history(char* list[], int cnt);
void insertHistory(char* str, int hiscnt);
int strParsing(char* list[], char* command, const char* delimeter);
void backgroundExecute(char* command[]);
void foregroundExecute(char* command[]);
