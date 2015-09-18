/* Internet Programming 2015/2016
 * 
 * Assignment 1
 * Authors:   Baris Can Vural,    Floris Turkenburg
 * VUNetID:   bvl250,             ftg600
 */



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

    struct sembuf p_up =   {0, 1, 0};
    struct sembuf p_down = {0, -1, 0};
    struct sembuf c_up =   {1, 1, 0};
    struct sembuf c_down = {1, -1, 0};

    sem = semget(IPC_PRIVATE, 2, 0600); /* Create 2 semaphores */

    semop(sem, &p_up, 1);

    int i;
    if (fork()) { // parent
        for (i = 0; i < 10; i++) {
            semop(sem, &p_down, 1);
            display("ab");
            semop(sem, &c_up, 1);
        }
        wait(NULL);
        // Destroy the semaphores after child and parent are both done.
        semctl(sem, 0, IPC_RMID); 
        semctl(sem, 1, IPC_RMID);
    }
    else { //child
        for (i = 0; i < 10; i++) {
            semop(sem, &c_down, 1);
            display("cd\n");
            semop(sem, &p_up, 1);
        }
    }

    return 0;
}