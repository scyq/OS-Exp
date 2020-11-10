#include "semaphore.h"
#include <pthread.h>
#include <stdio.h>

#define SHARE 1

void *read1(void *arg);         /* reader thread 1 */
void *read2(void *arg);         /* reader thread 2 */
void *plus_thread(void *arg);   /* plus thread */
void *mul_thread(void *arg);    /* mul_thread */

int main()
{
    int line = 0;   /* shall read which line */
    sem_t buffer[2];

    sem_init(&buffer[0], SHARE, 1);
    sem_init(&buffer[1], SHARE, 1);

}