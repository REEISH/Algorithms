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

int *partition(int *A, int start, int end)
{
    int *result = (int *)malloc(2 * sizeof(int));
    int pivot = A[end - 1]; // using last element as pivot

    int i = start - 1; // Element shorter than pivot
    int Length = 0;    // Element equal to pivot

    // while start ------- end if element is less than pivot swap to it's left
    for (int j = start; j <= end - 1; j++)
    {
        if (A[j - 1] < pivot)
        {
            i++; // increase
            if (i + Length < j)
            {
                swap(&A[i + Length - 1], &A[i - 1]); // At the end remove and replace
                swap(&A[i - 1], &A[j - 1]);          // Swap as normal partition does
            }
            else if ((i + Length) == j)
            {
                swap(&A[j - 1], &A[i - 1]);
            }
        }
        else if (A[j - 1] == pivot) // If equal to pivot
        {
            Length++;                            // Length increases
            swap(&A[j - 1], &A[i + Length - 1]); // Swap to length
        }
    }

    swap(&A[i + Length], &A[end - 1]); // the end element
    result[0] = i + 1;                 // Element shorter than pivot + 1
    result[1] = i + Length;            // Element larger than pivot - 1

    return result;
}

void quickSort(int *A, int start, int end)
{
    int *parter; // partingElement
    if (start < end)
    {
        parter = partition(A, start, end);

        quickSort(A, start, parter[0] - 1);
        quickSort(A, parter[1] + 1, end);
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

// THIS CODE WORKS WELL, HOWEVER
// THIS CODE IS NOT FULLY FURNISHED YET, USE CAREULLY
//  MIGHT GIVE SOME ERROR