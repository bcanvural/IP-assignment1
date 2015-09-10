
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    char cmd[100];
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
        
        pid = fork();
        
        if(pid == -1){
            perror("Fork error");
            exit(1);
        }
        
        //child process
        else if(pid==0){
            execlp(cmd,cmd, NULL);
            printf("command not found\n");
        } else {
            //wait for child process
            int childStatus;
            waitpid(pid, &childStatus, 0);
        }
    }
    return 0;
}