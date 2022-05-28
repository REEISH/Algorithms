#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
typedef long long int LONG;

void scanArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

LONG max(LONG a, LONG b)
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

// NAIVE METHOD
LONG fib(int N)
{
    if (N == 0 || N == 1)
    {
        return 1;
    }
    else
    {
        return fib(N - 1) + fib(N - 2);
    }
}

// BOTTOM UP METHOD
LONG bottomUpFib(int N)
{
    LONG R[N + 1];
    if (N == 0 || N == 1)
    {
        return 1;
    }
    R[0] = 1;
    R[1] = 1;
    for (int i = 2; i <= N; i++)
    {
        R[i] = R[i - 1] + R[i - 2];
    }
    return R[N];
}

// Memoized version
LONG fibMemoAux(int N, LONG *R)
{
    LONG result = 1;
    if (R[N] > 1)
    {
        return R[N];
    }
    else if (N == 0 || N == 1)
    {
        return result;
    }
    else
    {
        result = fibMemoAux(N - 1, R) + fibMemoAux(N - 2, R);
    }
    R[N] = result;
    return result;
}

LONG fibMemo(int N)
{
    LONG R[N + 1];
    for (int i = 0; i <= N; i++)
    {
        R[i] = 1;
    }
    return fibMemoAux(N, R);
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N; // Max num of elements
    printf("Enter a integer N:");
    scanf("%d", &N);
    // LONG ans = fib(N);         // NAIVE METHOD
    //LONG ans = bottomUpFib(N); // Bottom up method
    //LONG ans = fibMemo(N);//Memoized version
    //printf("fibonacci[%d] = %lld\n", N, ans);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}