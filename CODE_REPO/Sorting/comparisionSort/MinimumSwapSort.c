#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#define WRONG 0
#define CORRECT 1
// Works for Distict Elements only
void Swap(int *A, int *B)
{
    int Temp = *A;
    *A = *B;
    *B = Temp;
}

void scanArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

void printArray(int *A, int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        printf("%d ", A[i - 1]);
    }
    printf("\n");
}

int GetOrder(int Num, int *A, int N)
{
    int Order = 1;
    for (int i = 1; i <= N; i++)
    {
        if (A[i - 1] < Num)
        {
            Order = Order + 1;
        }
    }
    return Order;
}

int MinimumSwapSort(int *A, int N)
{
    int SwapNum = 0;
    int OrderGet[N];
    int Mark[N];
    // Get  Correct Location of the Elements
    for (int i = 1; i <= N; i++)
    {
        OrderGet[i - 1] = GetOrder(A[i - 1], A, N);
    }

    // Mark all Orders as per Correct or Wrong
    for (int i = 1; i <= N; i++)
    {
        if (OrderGet[i - 1] == i)
        {
            Mark[i - 1] = CORRECT;
        }
        else
        {
            Mark[i - 1] = WRONG;
        }
    }

    // Check all elemnts that are interchanged and swap them
    // Finally all elements are a non interchangable and hence swap each one
    // to their right position
    for (int i = 1; i <= N; i++)
    {
        while (Mark[i - 1] != CORRECT)
        {
            int temp = OrderGet[i - 1];
            Swap(&A[i - 1], &A[OrderGet[i - 1] - 1]);
            Swap(&OrderGet[i - 1], &OrderGet[OrderGet[i - 1] - 1]);
            SwapNum = SwapNum + 1;
            Mark[temp - 1] = CORRECT;
            if (OrderGet[i - 1] == i)
            {
                Mark[i - 1] = CORRECT;
            }
        }
    }
    return SwapNum;
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
    int MinSwap = MinimumSwapSort(Array, N);
    printf("Min Swap to Sort Array:%d\n", MinSwap);
    printArray(Array, 1, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}