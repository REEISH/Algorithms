#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
// Use gcc radixSort.c -lm to compile
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

int maxArray(int *A, int N)
{
    int maxIndex = 1;
    for (int i = 1; i <= N; i++)
    {
        if (A[i - 1] >= A[maxIndex - 1])
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}
double logarithm(int NUM, int BASE)
{
    double RES;
    RES = (log10(NUM) / log10(BASE));
    return RES;
}

int digits(int Num, int Base)
{
    int digit;
    digit = (logarithm(Num, Base)) + 1;
    return digit;
}

int DigitReach(int NUM, int DigitGet, int Base)
{
    while (DigitGet > 1)
    {
        NUM /= Base;
        DigitGet--;
    }
    return NUM % Base;
}

void countingSort(int *A, int *B, int k, int N, int digits)
{
    int C[k + 1];
    for (int i = 0; i <= k; i++)
    {
        C[i] = 0;
    }

    for (int j = 1; j <= N; j++)
    {
        C[DigitReach(A[j - 1], digits, k + 1)] = C[DigitReach(A[j - 1], digits, k + 1)] + 1;
    }
    for (int i = 1; i <= k; i++)
    {
        C[i] = C[i] + C[i - 1];
    }

    for (int j = N; j >= 1; j--)
    {
        B[C[DigitReach(A[j - 1], digits, k + 1)] - 1] = A[j - 1];
        C[DigitReach(A[j - 1], digits, k + 1)] = C[DigitReach(A[j - 1], digits, k + 1)] - 1;
    }
    for (int i = 0; i < N; i++)
    {
        A[i] = B[i];
    }
}

void radixSort(int *A, int *B, int N, int digits, int Base)
{

    for (int i = 1; i <= digits; i++)
    {
        countingSort(A, B, Base - 1, N, i);
    }
}

int main()
{

    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter a integer N:\n");
    scanf("%d", &N);
    int k;
    printf("Enter a integer d(max digits in element of array):"); // give by intution
    scanf("%d", &k);
    int Array[N];
    int Result[N];
    printf("Enter the array:\n");
    scanArray(Array, N);
    radixSort(Array, Result, N, k, 10);// For now numbers are in base 10, modify as per change.
    printArray(Result, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}

// The indexing of C arrays is done to make sure the output is right
