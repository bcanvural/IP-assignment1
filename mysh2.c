
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void parseCmd(char*,char**);

int main(int argc, const char * argv[]) {
    // insert code here...
    char cmd[100];
    char* params[10];
    pid_t pid;
    
    while(1) {
        //read command
        if(fgets(cmd, sizeof(cmd), stdin) == NULL) break;
        
        //remove any trailing end of line characters
        if(cmd[strlen(cmd)-1] == '\n') {
            cmd[strlen(cmd)-1] = '\0';
        }
        
        if(strcmp(cmd, "exit") == 0) {
            printf("bye");
            return 0;
        }
        
//        //printf(argv[0]);
//        for(int i=0;i<argc;i++){
//            printf("%s\n",argv[i]);
//        }
        
        
        
        pid = fork();
        
        if(pid == -1){
            perror("Fork error");
            exit(1);
        }
        else if(pid==0){
            //child process
            parseCmd(cmd, params);
            execvp(cmd, params);
            printf("command not found\n");
        } else {
            //wait for child process
            int childStatus;
            waitpid(pid, &childStatus, 0);
        }
    }
    return 0;
}

void parseCmd(char* cmd, char** params){
    for (int i=0; i<10; i++) {
        params[i] = strsep(&cmd, " ");
        if(params[i] == NULL) break;
    }
}