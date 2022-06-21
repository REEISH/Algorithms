#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void exchange(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int getMinIndex(int *A, int start, int end)
{
    int MIN = A[start - 1];
    int MinIndex = start;
    for (int i = start; i < end; i++)
    {
        if (MIN > A[i])
        {
            MIN = A[i];
            MinIndex = i + 1;
        }
    }
    return MinIndex;
}

void selectionSort(int *A, int N)
{
    int MIN;
    for (int i = 1; i < N; i++)
    {
        MIN = getMinIndex(A, i, N);
        exchange(&A[MIN - 1], &A[i - 1]);
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
    printf("Enter a array of length N:\n");
    scanArray(Array, N);
    selectionSort(Array, N);
    printArray(Array, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}