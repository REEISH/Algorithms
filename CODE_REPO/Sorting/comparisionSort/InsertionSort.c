#include <stdio.h>
#include <string.h>
#include <time.h>
// insertion sort

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
void insertionSort(int *array, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        int key = array[i];
        int j = i - 1;
        while ((j >= start - 1) && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
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
    // insertion sort
    insertionSort(Array, 1, N);
    printArray(Array, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}