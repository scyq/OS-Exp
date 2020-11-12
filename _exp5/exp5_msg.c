#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 100

int open_queue(int key_val)
{
    int qid;
    qid = msgget(key_val, IPC_CREAT | 0666);
    if (qid == -1)
    {
        perror("Failed to call a msgget");
        return -1;
    }
    return qid;
}

int main()
{
    pid_t sender;
    pid_t receiver;

    int msqid = open_queue(0);

    if (msqid == -1)
    {
        exit(1);
    }
    else
    {
        printf("Msg Queue Created.\n");
    }

    sender = fork();
    if (sender == 0)
    {
        char buffer[BUFFER_SIZE]; /* declare here to save mem */
        while (1)
        {
            scanf("%s", buffer);
            if (msgsnd(msqid, buffer, strlen(buffer), IPC_NOWAIT) == -1)
            {
                printf("%d\n", errno);  /* Err code 13 is Permission Denied */
                printf("Msg send err！\n");
                exit(1);
            }
            /* if the input is 'exit' then close the queue and quit */
            if (!strcmp(buffer, "exit"))
            {
                msgctl(msqid, IPC_RMID, NULL); /* delete the message queue */
                break;
            }
        }
        exit(0);
    }
    else if (sender > 0)
    {
        char buffer[BUFFER_SIZE]; /* declare here to save mem */
        receiver = fork();
        if (receiver == 0)
        {
            while (1)
            {
                ssize_t len =  msgrcv(msqid, buffer, BUFFER_SIZE, 0, MSG_NOERROR);
                if (!strcmp(buffer, "exit")) break;
                if (len > 0) printf("The message is '%s' .\n", buffer);
            }
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

    return 0;
}