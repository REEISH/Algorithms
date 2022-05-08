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

void printArray(int *A, int Start, int end)
{
    for (int i = Start; i <= end; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void countingSort(int *A, int *B, int k, int N)
{
    int C[k + 1];
    for (int i = 0; i <= k; i++)
    {
        C[i] = 0;
    }

    for (int j = 1; j <= N; j++)
    {
        C[A[j - 1]] = C[A[j - 1]] + 1;
    }
    for (int i = 1; i <= k; i++)
    {
        C[i] = C[i] + C[i - 1];
    }

    for (int j = N; j >= 1; j--)
    {
        B[C[A[j - 1]]] = A[j - 1];
        C[A[j - 1]] = C[A[j - 1]] - 1;
    }
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter a integer N:\n");
    scanf("%d", &N);
    int k;
    printf("Enter a integer k>(max element of array):");
    scanf("%d", &k);
    int Array[N];
    int Result[N + 1];
    /*for (int i = 0; i <= N; i++)
    {
        Result[i - 1] = 0;
    }*/
    printf("Enter the array:\n");
    scanArray(Array, N);
    countingSort(Array, Result, k, N);
    printArray(Result, 1, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}

// The indexing of C arrays is done to make sure the output is right
