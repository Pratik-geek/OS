// Client.c reading from shared memory
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string>

int main()
{
    char *shm_ptr;
    char buff[100];
    int shmid;
    shmid = shmget((key_t), 2345, 1024, 0666);
    printf("Key is %d\n", shmid);

    shm_ptr = shmat(shmid, NULL, 0);
    printf("Proess attached at%p", shm_ptr);
    printf("Data read frm is:%s\n", (char *)shm_ptr);
}