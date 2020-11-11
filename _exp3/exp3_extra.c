#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* quick sort */
void swap(int *a, int *b)
{
    int t = *b;
    *b = *a;
    *a = t;
}

void depart(int arr[], int start, int end)
{
    if (start >= end)
        return;
    int pivot = arr[end];
    int left = start;
    int right = end - 1;
    while (left < right)
    {
        while (left < right && arr[left] < pivot)
            left++;
        while (left < right && arr[right] > pivot)
            right--;
        swap(&arr[left], &arr[right]);
    }
    if (arr[left] >= arr[end])
        swap(&arr[left], &arr[end]);
    else
        left++;
    if (left)
        depart(arr, start, left - 1);
    depart(arr, left + 1, end);
}

void sort(int arr[], int len)
{
    depart(arr, 0, len - 1);
}

void sort_reverse(int arr[], int len)
{
    depart(arr, 0, len - 1);
    int temp[len];
    for (int i = 0; i < len; i++)
        temp[len - i - 1] = arr[i];
    for (int i = 0; i < len; i++)
        arr[i] = temp[i];
}

/* ------------------------------------------------------------ */
/* main process */

void *sort_thread(void *arg);
void *re_sort_thread(void *arg);

int main()
{
    int arr[10] = {1, 4, 7, 9, 0, 3, 2, 5, 6, 8};

    pthread_t tid_0, tid_1;
    int re_code0, re_code1;

    re_code0 = pthread_create(&tid_0, NULL, sort_thread, arr);
    if (re_code0)
    {
        printf("Thread Create Err");
        exit(1);
    }
    else
    {
        pthread_join(tid_0, NULL); /* wait thread 0 finished */
    }
    re_code1 = pthread_create(&tid_1, NULL, re_sort_thread, arr);
    if (re_code1)
    {
        printf("Thread Create Err");
        exit(1);
    }
    else
    {
        pthread_join(tid_1, NULL);
        printf("Two threads executed.\n");
    }
}

void *sort_thread(void *arg)
{
    int *arr = arg;
    sort(arr, 10);
    printf("Small to Big: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    pthread_exit(0);
}

void *re_sort_thread(void *arg)
{
    int *arr = arg;
    printf("Big to Small: ");
    for (int i = 9; i >= 0; i--)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    pthread_exit(0);
}