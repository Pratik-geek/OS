#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/shm.h>
#include<string.h>

int main(){
    char buff[100];
    int shmid;
    char *shm_ptr;
    shmid=shmget((key_t)2345, 1024, 0666| IPC_CREAT);
    printf("Key of shared mempry is %d\n", shmid);

    shm_ptr=shmat(shmid, NULL, 0);

    printf("Process attached at %p\n", shm_ptr);

    printf("ENter the details:\n");

    read(0, buff, 100);

    strcpy(shm_ptr, buff);
    printf("YOu wrote:%s\n", (char *)shm_ptr);





}