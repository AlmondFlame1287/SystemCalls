#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <syscall.h>
#include <wait.h>

FILE* file;

void signal_handler(int);


int main() {
    pid_t figli[3];
    signal(SIGUSR1, signal_handler);


    file = fopen("file.dat", "w+");

    figli[0] = fork();    

    if (figli[0] == 0) {
        // figlio1
        printf("PRIMO FIGLIO [%d]\n", getpid());
        sleep(10);
    } else if(figli[0] > 0) {
        // padre
        figli[1] = fork();
        if(figli[1] == 0) {
            printf("SECONDO FIGLIO [%d]\n", getpid());
            // figlio2
            sleep(10);
        } else if(figli[1] > 0) {
            // padre
            figli[2] = fork();
            if (figli[2] == 0) {
                // figlio3
                printf("TERZO FIGLIO [%d]\n", getpid());
                sleep(10);
            } else if(figli[2] > 0) {
                // padre
                fprintf(file, "%d %d, %d %d, %d %d", figli[0], 1, figli[1], 2, figli[2], 3);
                sleep(3);

                fclose(file);

                for (int i = 0; i < 3; i++)
                {
                    printf("esce?\n");

                    kill(figli[i], SIGUSR1);
                    sleep(1);
                }
                
            }
        }
    } else {
        perror("Error");
        exit(1);
    }


    return EXIT_SUCCESS;
}

void signal_handler(int signal_number) {
    if(signal_number == SIGUSR1){
        char* parList[] = {"./afterexec", NULL};

        execv("./afterexec", parList);
    }
}

