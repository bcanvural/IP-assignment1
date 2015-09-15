
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RESET               "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define MAX_CWD_SIZE             1024
#define MAX_PARAMS                 10

int parseCmd(char*,char**); // returns amount of arguments found

int main(int argc, const char * argv[]) {
    // insert code here...
    char cmd[100];
    char* params[MAX_PARAMS];
    char* params1[MAX_PARAMS];
    char* params2[MAX_PARAMS];
    pid_t pid;
    int p[2];
    int is_pipe = 0;
    int arg_count;
    
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
        
        arg_count = parseCmd(cmd, params);
        int i;
        for (i = 0; i < arg_count; i++) {
            if (strcmp(params[i], "|") == 0) {
                // If pipesymbol is found, put the arguments before and after 
                // the pipe in two separate arrays
                int j;
                for (j = 0; j < i; j++) {
                    params1[j] = params[j];
                }
                params1[i] = NULL;
                for (j = 0; j < MAX_PARAMS-i-1; j++) {
                    params2[j] = params[i+1+j];
                }
                params2[MAX_PARAMS-i-1] = NULL;
                
                if (pipe(p) < 0) {
                    perror("Error pipe");
                    exit(1);
                }

                is_pipe = 1;
                break;


            }
        }

        pid = fork();
        
        if (pid == -1) {
            perror("Fork error");
            exit(1);
        }
        else if (pid == 0) {
            // child process
            if (is_pipe) {
                close(p[0]);
                if (dup2(p[1], STDOUT_FILENO) < 0) {
                    perror("Output pipe failed");
                    exit(1);
                }
                execvp(params1[0], params1);
                printf("Command not found!\n");
            }
            else {
                execvp(cmd, params);
                printf("Command not found!\n");
            }
            return 0;
        } 
        else {
            if (is_pipe) {
                close(p[1]);
            }
            // wait for child process
            int childStatus;
            waitpid(pid, &childStatus, 0);

            if (is_pipe) {
                is_pipe = 0;
                pid = fork();

                if (pid < 0) {
                    perror("Second Fork error");
                    exit(1);
                }
                else if (pid == 0) { // child
                    close(p[1]);
                    if (dup2(p[0], STDIN_FILENO) < 0) {
                        perror("Input pipe failed");
                        exit(1);
                    }
                    
                    execvp(params2[0], params2);
                    printf("Command not found!\n");
                    return 0;
                }
                else {
                    waitpid(pid, &childStatus, 0);
                }

            }

        }
    }
    return 0;
}

int parseCmd(char* cmd, char** params) {
    int i;
    for (i = 0; i < MAX_PARAMS; i++) {
        params[i] = strsep(&cmd, " ");
        if (params[i] == NULL) break;
    }

    return i;
}