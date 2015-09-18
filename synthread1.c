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
#include <pthread.h>

pthread_mutex_t mutex;

void display(char *str) {
    char *tmp;
    for (tmp = str; *tmp; tmp++) {
        write(1, tmp, 1);
        usleep(100);
    }
}

void *thread_function(void *param) {
    int i;
    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        display("Bonjour monde\n");
        pthread_mutex_unlock(&mutex);
    }
}

int main() {

    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutex_init(&mutex, &mutex_attr);

    pthread_t thread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&thread, &attr, thread_function, NULL);

    int i;

    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        display("Hello world\n");
        pthread_mutex_unlock(&mutex);
    }
    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}