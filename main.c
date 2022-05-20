#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <signal.h>

FILE *fp;
sem_t mutex;
int count = 0;

void lavoro() {
    sem_wait(&mutex);

    // Apri il file figli.dat in append+read mode
    fp = fopen("./figli.dat", "a+r");

    // Aggiungi il pid del figlio e l'ordine di creazione
    fprintf(fp, "%d %d", getpid(), count);
    fprintf(fp, "\n");

    // Chiudi il file
    fclose(fp);

    // Variabile d'ordine per i figli
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
            kill(pids[i], SIGUSR1);
            break;
    }

    // attendi figli
    for (int i = 0; i < 3; i++)
    {
        waitpid(pids[i], NULL, 0);
    }
    
    // distruggi il semaforo quando finito
    sem_destroy(&mutex);
}