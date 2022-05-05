#include <stdio.h>
#include <string.h>
// insertion sort

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
void insertionSort(int *array, int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}
void main()
{
    int n; // number of elements in array
    printf("Enter a integer n;");
    scanf("%d", &n);
    int array[n];
    printf("Enter the array of lenght n:");
    scanArray(array, n); // reading the array

    // insertion sort
    insertionSort(array, n);
    printArray(array, n);
}