#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

/* handler function */
static void signal_catcher(int signal_no)
{
    if (signal_no == 2)
    {
        printf("Signal ID is %d. Speaker is %d.\n", signal_no, getpid());
        printf("You are trying to interrupt the progress.No way!\n");
    }
    else if (signal_no == SIGUSR1)
    {
        printf("Signal ID is %d, PID is %d\n", signal_no, getpid());
        printf("Yours, Parent Process.\n");
    }
    else
    {
        printf("Signal ID is %d.\n", signal_no);
        printf("Doesn't Matter.\n");
    }
}

int main()
{
    if (signal(SIGINT, signal_catcher) == SIG_ERR)
    {
        printf("Signal Catch Err.\n");
        exit(1);
    }

    pid_t child;
    child = fork();
    if (child == 0)
    {
        printf("Child Process On.\n");

        /* Parent send signal1 */
        if (signal(SIGUSR1, signal_catcher) == SIG_ERR)
        {
            printf("Signal Catch Err.\n");
            exit(1);
        }

        while (1)
        {
            pause();
        }
        exit(0);
    }
    else if (child > 0)
    {

        printf("Parent Process Ready.\n");
        sleep(1);   /* wait for child process ready */
        kill(child, SIGUSR1);
        wait(NULL);
    }
    else
    {
        printf("Fork Err.\n");
        exit(1);
    }

    return 0;
}