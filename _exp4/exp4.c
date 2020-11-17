#include "semaphore.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SHARE 1

void *read1(void *arg);       /* reader thread 1 */
void *read2(void *arg);       /* reader thread 2 */
void *plus_thread(void *arg); /* plus thread */
void *mul_thread(void *arg);  /* mul_thread */
int buffer[2];
int buffer_index = 0;
sem_t buffer_size;
sem_t read_lock;
sem_t number_counts;

int main()
{

    sem_init(&read_lock, SHARE, 1);
    sem_init(&number_counts, SHARE, 0);
    sem_init(&buffer_size, SHARE, 2);

    pthread_t r1, r2, o1, o2;
    int r_r1, r_r2, r_o1, r_o2;
    r_r1 = pthread_create(&r1, NULL, read1, NULL);
    r_r2 = pthread_create(&r2, NULL, read2, NULL);
    r_o1 = pthread_create(&o1, NULL, plus_thread, NULL);
    r_o2 = pthread_create(&o2, NULL, mul_thread, NULL);

    if (r_r1 && r_r2)
    {
        printf("Thread Create Err");
        exit(1);
    }
    else
    {
        pthread_join(r1, NULL);
        pthread_join(r2, NULL);
    }

    return 0;
}

void *read1(void *arg)
{
    FILE *fp = fopen("./1.dat", "r");
    if (fp)
    {
        while (!feof(fp))
        {
            sem_wait(&buffer_size);
            sem_wait(&read_lock);
            fscanf(fp, "%d", &buffer[buffer_index]);
            buffer_index = (buffer_index + 1) % 2;
            if (buffer_index == 0)
            {
                sem_post(&number_counts);
            }
            sem_post(&read_lock);
        }
        fclose(fp);
        pthread_exit(0);
    }
    else
    {
        printf("Open File Err\n");
        exit(1);
    }
}

void *read2(void *arg)
{
    FILE *fp = fopen("./2.dat", "r");
    if (fp)
    {
        while (!feof(fp))
        {
            sem_wait(&buffer_size);
            sem_wait(&read_lock);
            fscanf(fp, "%d", &buffer[buffer_index]);
            buffer_index = (buffer_index + 1) % 2;
            if (buffer_index == 0)
            {
                sem_post(&number_counts);
            }
            sem_post(&read_lock);
        }
        fclose(fp);
        pthread_exit(0);
    }
    else
    {
        printf("Open File Err\n");
        exit(1);
    }
}

void *plus_thread(void *arg)
{
    while (1)
    {
        sem_wait(&number_counts);
        printf("%d + %d = %d\n", buffer[0], buffer[1], buffer[0] + buffer[1]);
        sem_post(&buffer_size);
        sem_post(&buffer_size);
    }
}

void *mul_thread(void *arg)
{
    while (1)
    {
        sem_wait(&number_counts);
        printf("%d * %d = %d\n", buffer[0], buffer[1], buffer[0] * buffer[1]);
        sem_post(&buffer_size);
        sem_post(&buffer_size);
    }
}