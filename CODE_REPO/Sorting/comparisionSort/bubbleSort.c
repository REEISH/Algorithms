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

void bubbleSort(int *A, int N)
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = N - 1; j > i; j--)
        {
            if (A[j] < A[j - 1])
            {
                exchange(&A[j], &A[j - 1]);
            }
        }
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
    bubbleSort(Array, N);
    printArray(Array, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}