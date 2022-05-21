#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <syscall.h>
#include <wait.h>

FILE* file;

void sig_handler(int signal_number);


int main() {
    pid_t figli[3];

    file = fopen("file.dat", "w+");

    figli[0] = fork();    

    if (figli[0] == 0) {
        // figlio1
        printf("PRIMO FIGLIO [%d]\n", getpid());
        sleep(3);
    } else if(figli[0] > 0) {
        // padre
        figli[1] = fork();
        if(figli[1] == 0) {
            printf("SECONDO FIGLIO [%d]\n", getpid());
            // figlio2
            sleep(3);
        } else if(figli[1] > 0) {
            // padre
            figli[2] = fork();
            if (figli[2] == 0) {
                // figlio3
                printf("TERZO FIGLIO [%d]\n", getpid());
                sleep(3);
            } else if(figli[2] > 0) {
                // padre
                fprintf(file, "%d %d, %d %d, %d, %d", figli[0], 1, figli[1], 2, figli[2], 3);
                sleep(3);

                for (int i = 0; i < 3; i++) {
                    signal(SIGUSR1, sig_handler);
                }
                             
            }
        }
    } else {
        perror("Error");
        exit(1);
    }

    fclose(file);

    return 0;
}

void sig_handler(int signal_number) {
    if(signal_number == SIGUSR1){
        char* parmList[] = {"void", NULL};
        char* envList[] = {NULL};

        execve("./afterexec", parmList, envList);
    }
}

