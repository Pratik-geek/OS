#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

int cnt = 0, num = 0;
const int N = 5;
sem_t reader, writer;
pthread_mutex_t mutex;

void *Reader(int *arg) // Reader function
{
    sem_wait(&reader);
    // pthread_mutex_lock(&mutex);
    cnt++;

    if (cnt == 1)
    {
        sem_wait(&writer);
    }

    // pthread_mutex_unlock(&mutex);
    sem_post(&reader);

    printf("Reader : %d, read : %d\n", *(arg), num);

    pthread_mutex_lock(&mutex);

    cnt--;

    if (cnt == 0)
    {
        sem_post(&writer);
    }

    pthread_mutex_unlock(&mutex);
}

void *Writer(int *arg) // Writer function
{
    sem_wait(&writer);
    num++;
    printf("Writer : %d, wrote : %d\n", *(arg), num);

    sem_post(&writer);
}

int main()
{
    pthread_t r[N], w[N];

    sem_init(&reader, 0, 1);
    sem_init(&writer, 0, 1);

    int i;

    while (1)
    {
        // thread creation
        for (i = 1; i <= N; ++i)
        {

            pthread_create(&r[i], NULL, (void *)Reader, (int *)&i);
            pthread_create(&w[i], NULL, (void *)Writer, (int *)&i);
        }

        // joining the two threads
        for (i = 1; i <= N; ++i)
        {
            pthread_join(r[i], NULL);
            pthread_join(w[i], NULL);
        }
    }

    return 0;
}
