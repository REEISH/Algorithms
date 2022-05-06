#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void scanArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomPermutation(int *A, int N)
{
    srand(time(NULL));
    for (int i = N - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&A[i], &A[j]);
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
void randomisedPartition(int *A, int start, int end)
{
    int index;
    srand(time(NULL));
    int j = rand() % (end) + 1;
    swap(&A[end - 1], &A[j - 1]);
   
}
void randomisedQuickSort(int *A, int start, int end)
{
    int parter; // partingElement
    if (start < end)
    {
        parter = partition(A, start, end);
        randomisedQuickSort(A, start, parter - 1);
        randomisedQuickSort(A, parter + 1, end);
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
    randomisedPartition(Array,1,N);
    randomisedQuickSort(Array, 1, N);
    printArray(Array, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}