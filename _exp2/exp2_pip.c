#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

int main()
{
    int fd[2]; /* pipe 0-read 1-write*/
    char buffer[MAX];
    pid_t child_pid0, child_pid1;

    /* create pipe failed */
    if (pipe(fd) == -1)
    {
        printf("Create pipe Err");
        exit(1);
    }

    child_pid0 = fork();
    /* Child Process */
    if (child_pid0 == 0)
    {
        close(fd[1]);
        int len = read(fd[0], buffer, sizeof(buffer));
        buffer[len] = 0;
        printf("%s\n", buffer);
    }
    /* Parent Process */
    else if (child_pid0 > 0)
    {
        close(fd[0]);
        char temp[MAX] = "Child0 is sending Message!";
        write(fd[1], temp, strlen(temp));
    }
    else
    {
        printf("Fork Err");
        exit(1);
    }

    child_pid1 = fork();
    if (child_pid1 == 0)
    {
        close(fd[1]);
        int len = read(fd[0], buffer, sizeof(buffer));
        buffer[len] = 0;
        printf("%s\n", buffer);
    }
    /* Parent Process */
    else if (child_pid1 > 0)
    {
        close(fd[0]);
        char temp[MAX] = "Child1 is sending Message!";
        write(fd[1], temp, strlen(temp));
    }
    else
    {
        printf("Fork Err");
        exit(1);
    }

    return 0;
}
