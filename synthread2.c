#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>

int display_ab = 1;
pthread_mutex_t mutex;
pthread_cond_t cv;

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
        while (display_ab == 1) {
            pthread_cond_wait(&cv, &mutex);
        }
        display("cd\n");
        display_ab = 1;
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&mutex);
    }
}

int main() {

    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutex_init(&mutex, &mutex_attr);
    pthread_cond_init(&cv, NULL);

    pthread_t thread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&thread, &attr, thread_function, NULL);

    int i;

    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        while (display_ab == 0) {
            pthread_cond_wait(&cv, &mutex);
        }
        display("ab");
        display_ab = 0;
        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&mutex);
    }
    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cv);

    return 0;
}