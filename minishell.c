#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h> 
#include <stdbool.h> 

void parse_command(char* command){
    int i=0;
    char *token = strtok(command, " \n");
    char *args[20];
    while (token != NULL){
        args[i]=token;
        i++;
        token = strtok(NULL, " \n");
    }
    if (strcmp(args[0],"exit")==0 ) exit(0);
}

int main(){
    char command[256];;
    while (1) {
        printf("minishell> ");
        fgets(command,255,stdin);
        parse_command(command); //à developper

    }
}