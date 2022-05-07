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

void TailRecursiveQuickSort(int *A, int start, int end)// Works like a stack
{
    int parter; // partingElement
    while (start < end)
    {
        parter = partition(A, start, end);
        TailRecursiveQuickSort(A, start, parter - 1);
        start = parter + 1;
    }
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter a integer N:");
    scanf("%d", &N);
    int Array[N];
    printf("Enter the array:\n");
    scanArray(Array, N);
    TailRecursiveQuickSort(Array, 1, N);
    printArray(Array, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}