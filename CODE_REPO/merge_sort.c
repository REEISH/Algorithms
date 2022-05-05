#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// all array elements are less than 10000 of the array
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

void merge(int* A, int p, int q, int r)
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
void mergeSort(int* A, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
    
}
void main()
{
    int n; // number of elements in array
    scanf("%d", &n);
    int array[n];
    scanArray(array, n); // reading the array
    // calling merge sort
    mergeSort(array, 1, n);
    printArray(array, n);
}