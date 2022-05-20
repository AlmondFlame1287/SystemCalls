#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

FILE *fp;
sem_t mutex;
int count = 0;

void lavoro() {
    sem_wait(&mutex);

    fp = fopen("./figli.dat", "a+r");
    fprintf(fp, "%d %d", getpid(), count);
    fprintf(fp, "\n");
    fclose(fp);

    count++;

    sem_post(&mutex);
}

int main() {
    // inizializza il semaforo
    sem_init(&mutex, 0, 1);
    
    pid_t pids[3];

    // crea figli    
    for (int i = 0; i < 3; i++) {
        pids[i] = fork();

        if (pids[i] == 0)
            lavoro();
        else if(pids[i] > 0)
            break;
    }

    // attendi figli
    for (int i = 0; i < 3; i++)

    // distruggi il semaforo quando finito
    sem_destroy(&mutex);
}