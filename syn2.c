#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

void display(char *str) {
    char *tmp;
    for (tmp = str; *tmp; tmp++) {
        write(1, tmp, 1);
        usleep(100);
    }
}

int main() {
    int sem;

    struct sembuf up =   {0, 1, 0};
    struct sembuf down = {0, -1, 0};

    sem = semget(IPC_PRIVATE, 1, 0600); /* Create semaphore */
    
    semop(sem, &up, 1);

    int i;
    if (fork()) { // parent
        for (i = 0; i < 10; i++) {
            semop(sem, &down, 1);
            display("ab");
            semop(sem, &up, 1);
        }
        wait(NULL);
        semctl(sem, 0, IPC_RMID); // Destroy the mutex after child and parent 
                                  // are both done.
    }
    else { //child
        for (i = 0; i < 10; i++) {
            semop(sem, &down, 1);
            display("cd\n");
            semop(sem, &up, 1);
        }
    }

    return 0;
}