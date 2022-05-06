#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

int CarrayIndexHandler(int i)
{
    return i - 1;
}

int parent(int i)
{
    return i / 2;
}

int leftChild(int i)
{
    return 2 * i;
}

int rightChild(int i)
{
    return 2 * i + 1;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// max heap if A[parent(i)] >= A[i]
void maxHeapify(int *A, int i, int heapSize)
{
    int Left = leftChild(i);
    int Right = rightChild(i);
    int Largest;
    if (Left <= heapSize && A[Left - 1] > A[i - 1])
    {
        Largest = Left;
    }
    else
    {
        Largest = i;
    }
    if (Right <= heapSize && A[Right - 1] > A[Largest - 1])
    {
        Largest = Right;
    }
    if (Largest != i)
    {
        swap(&A[i - 1], &A[Largest - 1]);
        maxHeapify(A, Largest, heapSize);
    }
}
// min heap if A[parent(i)] <= A[i]
void minHeapify(int *A, int i, int heapSize)
{
    int Left = leftChild(i);
    int Right = rightChild(i);
    int Smallest;
    if (Left <= heapSize && A[Left - 1] < A[i - 1])
    {
        Smallest = Left;
    }
    else
    {
        Smallest = i;
    }
    if (Right <= heapSize && A[Right - 1] < A[Smallest - 1])
    {
        Smallest = Right;
    }
    if (Smallest != i)
    {
        swap(&A[i - 1], &A[Smallest - 1]);
        minHeapify(A, Smallest, heapSize);
    }
}

void buildMaxHeap(int *A, int heapSize)
{
    // array Length
    int i = heapSize / 2;
    for (i; i >= 1; i--)
    {
        maxHeapify(A, i, heapSize);
    }
}

void buildMinHeap(int *A, int heapSize)
{
    // array Length
    int i = heapSize / 2;
    for (i; i >= 1; i--)
    {
        minHeapify(A, i, heapSize);
    }
}
// heapSort using max heap
void heapSortMax(int *A, int N)
{
    int heapSize = N;
    buildMaxHeap(A, heapSize);
    for (int i = N; i >= 2; i--)
    {
        swap(&A[0], &A[i - 1]);
        heapSize = heapSize - 1;
        maxHeapify(A, 1, heapSize);
    }
}

// heapsort using min heap
void heapSortMin(int *A, int N)
{
    int heapSize = N;
    buildMinHeap(A, heapSize);

    for (int i = N; i >= 2; i--)
    {
        swap(&A[0], &A[i - 1]);
        heapSize = heapSize - 1;
        minHeapify(A, 1, heapSize);
    }
}

// Priority queues implementation as heaps
// priority queues as max heaps
// index 1 to N are elements ====>>> associated to a key , denoted byA[i], where i
// belongs to 1_______N.

int heapMaximum(int *A)
{
    return A[0];
}

int heapExtractMax(int *A, int heapSize)
{

    if (heapSize < 1)
    {
        exit(EXIT_FAILURE);
    }
    int maxElement = A[0];
    A[0] = A[heapSize - 1];
    heapSize = heapSize - 1;
    maxHeapify(A, 1, heapSize);
    return maxElement;
}

void heapIncreaseKey(int *A, int i, int key)
{
    if (key < A[i - 1])
    {
        printf("New key is smaller than the curent key");
        return;
    }
    A[i - 1] = key;
    while (i > 1 && A[parent(i) - 1] < A[i - 1])
    {
        swap(&A[i - 1], &A[parent(i) - 1]);
        i = parent(i);
    }
}

void maxHeapInsert(int *A, int heapSize, int key)
{
    heapSize = heapSize + 1;
    A[heapSize - 1] = INT_MIN;
    heapIncreaseKey(A, heapSize, key);
}

// priority queues as min heaps
// index 1 to N are elements ====>>> associated to a key , denoted byA[i], where i
// belongs to 1_______N.
int heapMinimum(int *A)
{
    return A[0];
}

int heapExtractMin(int *A, int heapSize)
{

    if (heapSize < 1)
    {
        exit(EXIT_FAILURE);
    }
    int minElement = A[0];
    A[0] = A[heapSize - 1];
    heapSize = heapSize - 1;
    minHeapify(A, 1, heapSize);
    return minElement;
}

void heapDecreaseKey(int *A, int i, int key)
{
    if (key > A[i - 1])
    {
        printf("New key is larger than the curent key");
        return;
    }
    A[i - 1] = key;
    while (i > 1 && A[parent(i) - 1] > A[i - 1])
    {
        swap(&A[i - 1], &A[parent(i) - 1]);
        i = parent(i);
    }
}

void minHeapInsert(int *A, int heapSize, int key)
{
    heapSize = heapSize + 1;
    A[heapSize - 1] = INT_MAX;
    heapDecreaseKey(A, heapSize, key);
}

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

int main()
{
    int N;
    printf("Enter a integer N:");
    scanf("%d", &N);
    int Array[N];
    printf("Enter the array:\n");
    scanArray(Array, N);
    heapSortMax(Array,N);
    //heapSortMin(Array, N);
    printArray(Array, N);
    return 0;
}