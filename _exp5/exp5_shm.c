#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main()
{
    pid_t sender;
    pid_t receiver;

    int shmid;
    int *mem_addr;

    /* 
        we only need two buffers in the condition
        head save the turn flag
        turn is represent for who is supposing to do
        0 - writer
        1 - reader
    */
    shmid = shmget(0, 2 * sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1)
    {
        printf("share memory get error\n");
        exit(1);
    }
    else
    {
        printf("Share mem got. ID is %d.\n", shmid);
    }

    sender = fork();
    if (sender == 0)
    {
        int *addr = (int *)shmat(shmid, NULL, 0);
        if ((addr == -1))
        {
            printf("Shmat Err, err code: %d\n", errno);
            exit(1);
        }
        int *p = addr + sizeof(int);
        for (int i = 0; i < 10; i++)
        {
            while (*addr != 0)
                ; /* busy waiting */
            scanf("%d", p);
            *addr = 1;
        }
        shmdt(addr); /* depart from shm */
        exit(0);
    }
    else if (sender > 0)
    {
        receiver = fork();
        if (receiver == 0)
        {
            int *addr = (int *)shmat(shmid, NULL, 0);
            if ((addr == -1))
            {
                printf("Shmat Err, err code: %d\n", errno);
                exit(1);
            }
            int *p = addr + sizeof(int);
            for (int i = 0; i < 10; i++)
            {
                while (*addr != 1)
                    ; /* busy waiting */
                printf("Square of number %d is %d.\n", i, *p * *p);
                *addr = 0;
            }
            shmdt(addr); /* depart from shm */
            exit(0);
        }
        else if (receiver > 0)
        {
            wait(NULL);
        }
        else
        {
            printf("Fork Err");
            exit(1);
        }
    }
    else
    {
        printf("Fork Err");
        exit(1);
    }

    shmctl(shmid, IPC_RMID, NULL); /* delete the share memory */
    return 0;
}