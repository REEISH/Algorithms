#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
// This is a greedy algorithm

// The problem is 0-1 knapsack (But in fractional)
// Just like the last time,
// the thief came to steal your house and take the most valuabe items
// while you went out with your wife on a movie.
// This time the thief came prepared and bought a magic cutter
// that can destroy any thing in dust and pick up the dust to full his knapSack
// Just like last time his knapSack has a maximum weight W.
// which he can comfortably carry.

typedef long long int LONG;

void scanArray(LONG *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%lld", &A[i]);
    }
}

void printArray(double *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%f ", A[i]);
    }
    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapD(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

void swapL(LONG *a, LONG *b)
{
    LONG temp = *a;
    *a = *b;
    *b = temp;
}

int partition(double *A, LONG *B, int *C, int start, int end)
{
    double pivot = A[end - 1]; // using last element as pivot
    int i = start - 1;
    // while start ------- end if element is less than pivot swap to it's left
    for (int j = start; j <= end - 1; j++)
    {
        if (A[j - 1] <= pivot)
        {
            i++;
            swapD(&A[i - 1], &A[j - 1]);
            swapL(&B[i - 1], &B[j - 1]);
            swap(&C[i - 1], &C[j - 1]);
        }
    }
    swapD(&A[i], &A[end - 1]);
    swapL(&B[i], &B[end - 1]);
    swap(&C[i], &C[end - 1]);
    return i + 1;
}

void quickSort(double *A, LONG *B, int *C, int start, int end)
{
    int parter; // partingElement
    if (start < end)
    {
        parter = partition(A, B, C, start, end);
        quickSort(A, B, C, start, parter - 1);
        quickSort(A, B, C, parter + 1, end);
    }
}

void KnapSackFractional(LONG *Weights, LONG *Cost, double *Result, int N, int W)
{
    int Item[N];
    double GreedyValue[N]; // to insert value per pound
    for (int i = 0; i < N; i++)
    {
        Result[i] = 0;
        Item[i] = i + 1;
        GreedyValue[i] = (double)((long double)Cost[i] / (long double)Weights[i]);
    }
    quickSort(GreedyValue, Weights, Item, 1, N);
    double LeftWeight = (double)W;
    int Start = N;
    while (LeftWeight > 0 && Start > 0)
    {
        if ((double)LeftWeight - (double)(Weights[Start - 1]) >= 0)
        {
            LeftWeight = LeftWeight - (double)(Weights[Start - 1]);
            Result[Item[Start - 1] - 1] = (double)Weights[Start - 1];
            Start = Start - 1;
        }
        else
        {
            double Frac = (double)LeftWeight / (double)Weights[Start - 1];
            LeftWeight = 0;
            Result[Item[Start - 1] - 1] = Frac * Weights[Start - 1];
        }
    }
    return;
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter the number of items you have:");
    scanf("%d", &N);
    LONG Weights[N];
    printf("Enter the weights of these items:\n");
    scanArray(Weights, N);
    LONG Cost[N];
    printf("Enter the cost of these items:\n");
    scanArray(Cost, N);
    int W;
    printf("Enter the maximum load of the knapsack:");
    scanf("%d", &W);
    double Result[N];
    KnapSackFractional(Weights, Cost, Result, N, W);
    printArray(Result, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}