#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

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
        for (int i = 0; i < 10; i++)
            printf("b");
        exit(0);
    }
    else
    {
        wait(NULL);
    }

    c_pid = fork();
    if (c_pid < 0)
    {
        printf("err");
    }
    else if (c_pid == 0)
    {
        for (int i = 0; i < 10; i++)
            printf("c");
        exit(0);
    }
    else
    {
        wait(NULL);
    }

    for (int i = 0; i < 10; i++)
        printf("a");

    return 0;
}