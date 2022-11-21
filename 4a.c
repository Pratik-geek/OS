#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

sem_t full, empty;
pthread_mutex_t mutex;
int buffer[10];
int cnt = 0;

void *producer(void *arg)
{

    sem_wait(&empty);

    pthread_mutex_lock(&mutex);

    buffer[cnt] = rand() % 10;
    printf("\n Producer %d produced %d", *((int *)arg), buffer[cnt]);
    cnt++;
    sleep(1);

    pthread_mutex_unlock(&mutex);

    sem_post(&full);
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    cnt--;
    printf("\n consumer %d consumed :%d", *((int *)arg), buffer[cnt]);
    sleep(1);
    pthread_mutex_unlock(&mutex);

    sem_post(&empty);
    pthread_exit(NULL);
}

int main()
{

    int np, nc;
    pthread_t p[10], c[10];

    pthread_mutex_init(&mutex, NULL);

    int i, j, k, l;

    printf("ENter profucers and cnsuemrs: ");
    scanf("%d %d", &np, &nc);

    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);

    for (i = 0; i < np; i++)
        pthread_create(&p[i], NULL, (void *)producer, (void *)&i);

    for (j = 0; j < nc; j++)
        pthread_create(&c[j], NULL, (void *)consumer, (void *)&j);

    for (k = 0; k < np; k++)
    {
        pthread_join(p[k], NULL);
    }
    for (l = 0; l < nc; l++)
    {
        pthread_join(c[l], NULL);
    }

    return 0;
}