#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

void scanArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

void printArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getMax(int *A, int N)
{
    int MAX = A[0];
    for (int i = 1; i < N; i++)
    {
        if (MAX < A[i])
        {
            MAX = A[i];
        }
    }
    return MAX;
}

int getMin(int *A, int N)
{
    int MIN = A[0];
    for (int i = 1; i < N; i++)
    {
        if (MIN > A[i])
        {
            MIN = A[i];
        }
    }
    return MIN;
}

int *GetMinAndMax(int *A, int N)
{
    int *MINMAX = (int *)malloc(2 * sizeof(int));
    MINMAX[0] = MINMAX[1] = A[0];
    for (int i = 0; i < N; i++)
    {
        if (MINMAX[1] > A[i])
        {
            MINMAX[1] = A[i];
        }
        else if (MINMAX[0] < A[i])
        {
            MINMAX[0] = A[i];
        }
    }
    return MINMAX;
}

int partition(int *A, int start, int end)
{
    int pivot = A[end - 1]; // using last element as pivot
    int i = start - 1;
    // while start ------- end if element is less than pivot swap to it's left
    for (int j = start; j <= end - 1; j++)
    {
        if (A[j - 1] <= pivot)
        {
            i++;
            swap(&A[i - 1], &A[j - 1]);
        }
    }
    swap(&A[i], &A[end - 1]);
    return i + 1;
}

int randomisedPartition(int *A, int start, int end)
{
    srand(time(NULL));
    int j = start + (rand() % (end - start + 1)); // start to end
    swap(&A[end - 1], &A[j - 1]);
    int result = partition(A, start, end);
    return result;
}
int randomisedSelect(int *A, int start, int end, int Order)
{
    if (start == end)
    {
        return A[start - 1];
    }
    int parter = randomisedPartition(A, start, end);
    int NUM = parter - start + 1;
    if (NUM == Order)
    {
        return A[parter - 1];
    }
    else if (Order < NUM)
    {
        return randomisedSelect(A, start, parter - 1, Order);
    }
    else
    {
        return randomisedSelect(A, parter + 1, end, Order - parter);
    }
}

void main()
{
    int N;
    int Order;
    printf("Enter a integer N:");
    scanf("%d", &N);
    int Array[N];
    printf("Enter the array:\n");
    scanArray(Array, N);
    printf("MAX:%d\n", getMax(Array, N));
    printf("MIN:%d\n", getMin(Array, N));
    printf("MAX:%d  MIN:%d\n", GetMinAndMax(Array, N)[0], GetMinAndMax(Array, N)[1]);
    printf("Enter a integer I(Order statistic you want to obtain):");
    scanf("%d", &Order);
    int result = randomisedSelect(Array, 1, N, Order);
    printf("%d\n", result);
}