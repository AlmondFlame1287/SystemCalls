#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <syscall.h>
#include <wait.h>

int main() {
    pid_t figli[3] = {0, 0, 0};

    for (int i = 0; i < 3; i++)
    {
        printf("SECONDO PROGRAMMA WOOOOOOO [%d]\n", figli[i]);
    }
    
}