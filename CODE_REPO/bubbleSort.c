#include <stdio.h>
#include <stdlib.h>

void scanArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
}
void printArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
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

void bubbleSort(int *A, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (A[j] < A[j - 1])
            {
                exchange(&A[j], &A[j - 1]);
            }
        }
    }
}

void main()
{
    int n;
    int a;
    printf("Enter a integer n:");
    scanf("%d", &n);
    int array[n];
    printf("Enter a array of length n:");

    scanArray(array, n);
    bubbleSort(array, n);
    printArray(array, n);
    
}