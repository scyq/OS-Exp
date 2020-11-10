#include <pthread.h>
#include <stdio.h>

void *char_thread(void *arg);
void *int_thread(void *arg);

int main()
{
    /*
        tid_0 thread 0 char_thread
        tid_1 thread 1 int_thread
    */
    pthread_t tid_0, tid_1;
    int re_code0, re_code1;
    char c = 'a';
    int i = 10;

    re_code0 = pthread_create(&tid_0, NULL, char_thread, &c);
    re_code1 = pthread_create(&tid_1, NULL, int_thread, &i);

    /* if err */
    if (re_code0 && re_code1)
    {
        printf("Thread Create Err");
        exit(1);
    }
    else
    {
        pthread_join(tid_0, NULL);
        pthread_join(tid_1, NULL);
    }

    return 0;
}

void *char_thread(void *arg)
{
    char *char_pointer = arg;
    printf("Char is %c\n", *char_pointer);
    pthread_exit(0);
}

void *int_thread(void *arg)
{
    int *int_pointer = arg;
    printf("Int is %d\n", *int_pointer);
    pthread_exit(0);
}