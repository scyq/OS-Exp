#include "semaphore.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SHARE 1

void *read1(void *arg);       /* reader thread 1 */
void *read2(void *arg);       /* reader thread 2 */
void *plus_thread(void *arg); /* plus thread */
void *mul_thread(void *arg);  /* mul_thread */
int num0;
int num1;
sem_t read_ready[2]; /* individual finished */
sem_t read_finished; /* both finished */
sem_t job_done;      /* reader have to wait the job done */
sem_t plus_ok;       /* plus thread ok to operate */
sem_t mul_ok;        /* multiple thread ok to operate */

int main()
{

    sem_init(&read_ready[0], SHARE, 0);
    sem_init(&read_ready[1], SHARE, 0);
    sem_init(&read_finished, SHARE, -1);
    sem_init(&job_done, SHARE, 0);
    sem_init(&plus_ok, SHARE, 1);
    sem_init(&mul_ok, SHARE, 0);

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
            fscanf(fp, "%d", &num0);
            sem_post(&read_ready[0]);
            sem_wait(&read_ready[1]); /* wait the other reader finished */
            sem_post(&read_finished);
            sem_wait(&job_done);
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
            fscanf(fp, "%d", &num1);
            sem_post(&read_ready[1]);
            sem_wait(&read_ready[0]); /* wait the other reader finished */
            sem_post(&read_finished);
            sem_wait(&job_done);
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
        sem_wait(&plus_ok);       /* check the order */
        sem_wait(&read_finished); /* judge if ok to do the job */
        printf("%d + %d = %d\n", num0, num1, num0 + num1);
        sem_wait(&read_finished); /* this thread get into wait queue */

        /* post 2 times make both reader1 and reader2 can read */
        sem_post(&job_done);
        sem_post(&job_done);

        sem_post(&mul_ok); /* wake multiple thread */
    }
}

void *mul_thread(void *arg)
{
    while (1)
    {
        sem_wait(&mul_ok);        /* check the order */
        sem_wait(&read_finished); /* judge if ok to do the job */
        printf("%d * %d = %d\n", num0, num1, num0 * num1);
        sem_wait(&read_finished); /* this thread get into wait queue */

        /* post 2 times make both reader1 and reader2 can read */
        sem_post(&job_done);
        sem_post(&job_done);

        sem_post(&plus_ok); /* wake multiple thread */
    }
}