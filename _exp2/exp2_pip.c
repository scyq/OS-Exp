#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

int main()
{
    int fd[2]; /* pipe 0-read 1-write*/
    char buffer[MAX];
    pid_t child_pid;

    /* create pipe failed */
    if (pipe(fd) == -1)
    {
        printf("Create pipe Err");
        exit(1);
    }

    child_pid = fork();
    /* Child Process */
    if (child_pid == 0)
    {
        close(fd[1]);
        int len = read(fd[0], buffer, sizeof(buffer));
        buffer[len] = 0;
        printf("Child: Messege from pipe is ' %s '\n", buffer);
        exit(0);
    }
    /* Parent Process */
    else if (child_pid > 0)
    {
        close(fd[0]);
        char temp[MAX] = "You are my child";
        write(fd[1], temp, strlen(temp));
        exit(0);
    }
    else
    {
        printf("Fork Err");
        exit(1);
    }
}
