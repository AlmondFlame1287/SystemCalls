#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <syscall.h>
#include <wait.h>

sem_t sem;
FILE* fp;

struct pid_info {
    pid_t pid[3];
    int num[3];
};

void signal_handler(int signal_number) {
    if(signal_number == SIGUSR2){
        exit(1);
    }
}

int main(int argc, char *argv[]) {

    sem_init(&sem, 0, 1);

    struct pid_info info;
    signal(SIGUSR2, signal_handler);

    fp = fopen("file.dat", "r");

    if(fp == NULL) {
        perror("couldn't read file");
        sleep(3);
    }
    
    sem_wait(&sem);

    fscanf(fp, "%d %d, %d %d, %d %d", &info.pid[0], &info.num[0], &info.pid[1], &info.num[1], &info.pid[2], &info.num[2]);
    fclose(fp);

    if(getpid() == info.pid[2] || getpid() == info.pid[1]) {
        printf("Siamo processi 3 e 2");
        kill(info.pid[0], SIGUSR2);
        sleep(1);
    } else {
        wait(NULL);
    }

    sem_post(&sem);

    sem_destroy(&sem);
    return EXIT_SUCCESS;
}
