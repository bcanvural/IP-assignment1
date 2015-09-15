
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RESET               "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define MAX_CWD_SIZE             1024
#define MAX_PARAMS                 10


void parseCmd(char*,char**);

int main(int argc, const char * argv[]) {
    // insert code here...
    char cmd[100];
    char* params[MAX_PARAMS];
    pid_t pid;
    
    while (1) {

        char cwd[MAX_CWD_SIZE];
        // Print the current working directory
        getcwd(cwd, MAX_CWD_SIZE);
        printf(BOLDGREEN "%s :> " RESET, cwd);
        // read command
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) break;
        
        // remove any trailing end of line characters
        if (cmd[strlen(cmd)-1] == '\n') {
            cmd[strlen(cmd)-1] = '\0';
        }
        
        if (strcmp(cmd, "exit") == 0) {
            printf("Exiting shell..\n");
            return 0;
        }
        
        
        
        pid = fork();
        
        if (pid == -1) {
            perror("Fork error");
            exit(1);
        }
        else if (pid == 0) {
            // child process
            parseCmd(cmd, params);
            execvp(cmd, params);
            printf("Command not found!\n");
            return 0;
        } 
        else {
            // wait for child process
            int childStatus;
            waitpid(pid, &childStatus, 0);
        }
    }
    return 0;
}

void parseCmd(char* cmd, char** params) {
    int i;
    for (i = 0; i < MAX_PARAMS; i++) {
        params[i] = strsep(&cmd, " ");
        if (params[i] == NULL) break;
    }
}