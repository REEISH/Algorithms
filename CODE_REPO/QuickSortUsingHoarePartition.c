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

int hoarePartition(int *A, int start, int end)
{
    int pivot = A[start - 1]; // using first element as pivot
    int i = start - 1;
    int j = end + 1;

    // while always find a pair of elements that are less/greater than pivot then swap them, les one to left and more to right
    while (1)
    {

        do
        {
            j = j - 1;
        } while (A[j - 1] > pivot);

        do
        {
            i = i + 1;
        } while (A[i - 1] < pivot);

        if (i >= j)
        {
            return j;
        }
        swap(&A[i - 1], &A[j - 1]);
    }
}

void quickSort(int *A, int start, int end)
{
    int parter; // partingElement
    if (start < end)
    {
        parter = hoarePartition(A, start, end);
        quickSort(A, start, parter);
        quickSort(A, parter + 1, end);
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
    quickSort(Array, 1, N);
    printArray(Array, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}
