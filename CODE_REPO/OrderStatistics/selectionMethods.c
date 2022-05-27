#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
// Use gcc selectionMethods.c -lm to compile
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

int getMax(int *A, int N)
{
    int MAX = A[0];
    for (int i = 1; i < N; i++)
    {
        if (MAX < A[i])
        {
            MAX = A[i];
        }
    }
    return MAX;
}

int getMin(int *A, int N)
{
    int MIN = A[0];
    for (int i = 1; i < N; i++)
    {
        if (MIN > A[i])
        {
            MIN = A[i];
        }
    }
    return MIN;
}

int *GetMinAndMax(int *A, int N)
{
    int *MINMAX = (int *)malloc(2 * sizeof(int));
    MINMAX[0] = MINMAX[1] = A[0];
    for (int i = 0; i < N; i++)
    {
        if (MINMAX[1] > A[i])
        {
            MINMAX[1] = A[i];
        }
        else if (MINMAX[0] < A[i])
        {
            MINMAX[0] = A[i];
        }
    }
    return MINMAX;
}

int linearSearch(int *A, int start, int end, int NUM)
{
    int j = 0;
    for (int i = start; i <= end; i++)
    {

        if (A[i - 1] == NUM)
        {
            j++;
            return i;
        }
        if (i == end && j == 0)
        {
            return -1;
        }
    }
}

void insertionSort(int *array, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        int key = array[i];
        int j = i - 1;
        while (j >= start - 1 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
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

int Partition(int *A, int start, int end, int pivot)
{
    swap(&A[end - 1], &A[pivot - 1]);
    int result = partition(A, start, end);
    return result;
}

int randomisedPartition(int *A, int start, int end)
{
    srand(time(NULL));
    int j = start + (rand() % (end - start + 1)); // start to end
    swap(&A[end - 1], &A[j - 1]);
    int result = partition(A, start, end);
    return result;
}

int randomisedSelect(int *A, int start, int end, int Order)
{
    if (start == end)
    {
        return A[start - 1];
    }
    int parter = randomisedPartition(A, start, end);
    int NUM = parter - start + 1;
    if (NUM == Order)
    {
        return A[parter - 1];
    }
    else if (Order < NUM)
    {
        return randomisedSelect(A, start, parter - 1, Order);
    }
    else
    {
        return randomisedSelect(A, parter + 1, end, Order - NUM);
    }
}

int Select(int *A, int start, int end, int Order)
{
    if (start == end)
    {
        return A[start - 1];
    }
    int parter = partition(A, start, end);
    int NUM = parter - start + 1;
    if (NUM == Order)
    {
        return A[parter - 1];
    }
    else if (Order < NUM)
    {
        return Select(A, start, parter - 1, Order);
    }
    else
    {
        return Select(A, parter + 1, end, Order - NUM);
    }
}

int SelectTemplate(int *A, int start, int end)
{
    if (start == end)
    {
        return A[start - 1];
    }
    int nElems = end - start + 1;
    // groups of 5
    int nParts = (int)ceil((double)(nElems / 5.0));
    int B[nParts];
    for (int i = 0; i < nParts; i++)
    {
        int start = 5 * (i) + 1;
        int end = 5 * (i) + 5;
        if (end > nElems)
        {
            end = nElems;
        }
        insertionSort(A, start, end);
        B[i] = A[(start + end) / 2 - 1];
    }
    int median = SelectTemplate(B, 1, nParts);
    return median;
}

int selectWrapper(int *A, int start, int end)
{
    int median = SelectTemplate(A, start, end);
    int medianIndex = linearSearch(A, start, end, median);
    int parter = Partition(A, start, end, medianIndex);
    return parter;
}

int SelectinLinearTime(int *A, int start, int end, int Order)
{
    if (start == end)
    {
        return A[start - 1];
    }
    int parter = selectWrapper(A, start, end);
    printf("parter:%d\n", parter);
    int NUM = parter - start + 1;
    if (NUM == Order)
    {
        return A[parter - 1];
    }
    else if (Order < NUM)
    {
        return Select(A, start, parter - 1, Order);
    }
    else
    {
        return Select(A, parter + 1, end, Order - NUM);
    }
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    int Order;
    printf("Enter a integer N:");
    scanf("%d", &N);
    int Array[N];
    printf("Enter the array:\n");
    scanArray(Array, N);
    printf("MAX:%d\n", getMax(Array, N));
    printf("MIN:%d\n", getMin(Array, N));
    printf("MAX:%d  MIN:%d\n", GetMinAndMax(Array, N)[0], GetMinAndMax(Array, N)[1]);
    printf("Enter a integer I(Order statistic you want to obtain):");
    scanf("%d", &Order);
    int result = Select(Array, 1, N, Order);
    printf("Select:%d\n", result);
    int resultRandomised = randomisedSelect(Array, 1, N, Order);
    printf("RandomisedSelect:%d\n", result);
    int resultInLinearTime = SelectinLinearTime(Array, 1, N, Order);
    printf("resultInLinearTime:%d\n", resultInLinearTime);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}