#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h> 
#include <stdbool.h> 

void readfile(char* search){
    FILE *file = fopen("help.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char line[256];
    if (strcmp(search, "*") == 0) {
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
    } else {
        // Print specific section
        char *symb = "~";
        int reading = 0;
        while (fgets(line, sizeof(line), file)) {
            if (strstr(line, search) != NULL) {
                reading = 1;
            }
            if (strstr(line, symb) != NULL) {
                reading = 0;
            }
            if (reading) {
                printf("%s", line);
            }
        }
    }
    fclose(file);
}

void parse_command(char* command){
    int i=0;
    char *token = strtok(command, " \n");
    char *args[20];
    args[1]="*";
    while (token != NULL){
        args[i]=token;
        i++;
        token = strtok(NULL, " \n");
    }
    if (strcmp(args[0],"exit")==0 ) exit(0);
    else if (strcmp(args[0],"help")==0 ) {
        if (args[1] != NULL) {
            readfile(args[1]);
        }
}} 

int main(){
    char command[256];;
    while (1) {
        printf("minishell> ");
        fgets(command,255,stdin);
        parse_command(command); //à developper

    }
}