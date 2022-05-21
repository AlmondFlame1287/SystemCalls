#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <syscall.h>
#include <wait.h>

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
    struct pid_info info;
    signal(SIGUSR2, signal_handler);

    pid_t figli[3] = {0, 0, 0};
    fp = fopen("file.dat", "w+");

    fscanf(fp, "%d %d, %d %d, %d %d", &info.pid[0], &info.num[0], &info.pid[1], &info.num[1], &info.pid[2], &info.num[2]);
    fclose(fp);

    for (int i = 0; i < 3; i++) {
        printf("Sono figlio %d e il mio numero e' %d\n", info.pid[i], info.num[i]);

        if(getpid() == info.pid[2] || getpid() == info.pid[1]) {
            kill(info.pid[0], SIGUSR2);
        } else {
            wait(NULL);
        }
    }
    
    return EXIT_SUCCESS;
}