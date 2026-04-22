#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h> 
#include <stdbool.h> 

void execute_external_command(char *args[]); // forward declaration

void readfile(const char* search){
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
        const char *symb = "~";
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
    int i = 0;
    char *token = strtok(command, " \n");
    char *args[20] = {NULL};

    while (token != NULL){
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    if (strcmp(args[0], "exit") == 0) exit(0);

    else if (strcmp(args[0], "help") == 0) {
        if (args[1] == NULL)
            readfile("*");
        else
            readfile(args[1]);
    }

    else if (strcmp(args[0], "cd") == 0) {
        if (args[1] != NULL) {
            if (chdir(args[1]) != 0)
                perror("cd error");
        } else {
            printf("cd: missing argument\n");
        }
    }

    else {
        execute_external_command(args);
    }
}

void execute_external_command(char *args[]) {
    pid_t pid = fork();

    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("exec error");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0) {
        wait(NULL);
    }
    else {
        perror("fork error");
    }
}

int main(){
    char command[256];

    while (1) {
        printf("\nminishell> ");

        if (fgets(command, 255, stdin) == NULL) {
            printf("\n");
            break;
        }

        parse_command(command);
    }

    return 0;
}