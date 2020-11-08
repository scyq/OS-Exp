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
        // _exit(0);
        return 0;
    }
    else
    {
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
        // _exit(0);
        return 0;
    }
    else
    {
    }

    for (int i = 0; i < 10; i++)
        printf("a");

    return 0;
}