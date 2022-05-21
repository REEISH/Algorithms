#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>

// all array elements are less than 10000 of the array
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

void merge(int *A, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1 + 1];
    int R[n2 + 1];
    for (int i = 0; i < n1; i++)
    {
        L[i] = A[p + i - 1];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = A[q + i];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i = 0;
    int j = 0;
    for (int k = p - 1; k < r; k++)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i = i + 1;
        }
        else
        {
            A[k] = R[j];
            j = j + 1;
        }
    }
}

void mergeSort(int *A, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(A, start, mid);
        mergeSort(A, mid + 1, end);
        merge(A, start, mid, end);
    }
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N; // number of elements in array
    printf("Enter a integer N:");
    scanf("%d", &N);
    int Array[N];
    printf("Enter the array of lenght N:\n");
    scanArray(Array, N); // reading the array
    // calling merge sort
    mergeSort(Array, 1, N);
    printArray(Array, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}