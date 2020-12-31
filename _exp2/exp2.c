#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t b_pid;
    pid_t c_pid;

    b_pid = fork();
    if (b_pid < 0)
    {
        printf("err");
    }
    else if (b_pid == 0)
    {
        printf("This is from process %d\n", getpid());
        for (int i = 0; i < 1000; i++)
            printf("b");
        printf("\n");
        exit(0);
    }

    c_pid = fork();
    if (c_pid < 0)
    {
        printf("err");
    }
    else if (c_pid == 0)
    {
        printf("This is from process %d\n", getpid());
        for (int i = 0; i < 1000; i++)
            printf("c");
        printf("\n");
        exit(0);
    }

    printf("This is from process %d\n", getpid());
    for (int i = 0; i < 1000; i++)
        printf("a");
    printf("\n");
    
    return 0;
}