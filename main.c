#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

void* lavoro() {
    sem_wait(&mutex);

    FILE* fp = fopen("./figli.dat", "w+");
    fprintf(fp, "%d", getpid());
    fprintf(fp, "\n");
    fclose(fp);

    sem_post(&mutex);
}


int main() {
    // Crea figli
    sem_init(&mutex, 0, 1);

    pthread_t threads[3];

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&threads[i], NULL, &lavoro, NULL);
        // sleep(2);
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&mutex);
    // pthread_t t1;
    // pthread_create(&t1, NULL, &lavoro, NULL);
    
    // pthread_join(t1, NULL);

    // int n;

    // FILE* f = fopen("./figli.dat", "w+");

    // if(f == NULL) {
    //     printf("ERRORE");
    //     exit(1);
    // }
    
    // printf("Dammi un numero ");
    // scanf("%d", &n);
    // fprintf(f, "%d", n);
    // fclose(f);
}