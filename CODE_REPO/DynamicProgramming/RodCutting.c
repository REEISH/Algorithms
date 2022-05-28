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

// NAIVE RECURIVE METHOD
LONG cutRod(int *price, int N)
{
    if (N == 0)
    {
        return 0;
    }
    LONG result = LONG_MIN;
    for (int i = 1; i <= N; i++)
    {
        result = max(result, (LONG)(price[i - 1] + cutRod(price, N - i)));
    }
    return result;
}

// top-down memoization version

LONG cutRodMemoAux(int *price, int N, LONG *R)
{
    if (R[N] >= 0)
    {
        return R[N];
    }
    LONG result;
    if (N == 0)
    {
        result = 0;
    }
    else
    {
        result = LONG_MIN;
    }
    for (int i = 1; i <= N; i++)
    {
        result = max(result, (LONG)(price[i - 1] + cutRodMemoAux(price, N - i, R)));
    }
    R[N] = result;
    return result;
}

LONG cutRodMemo(int *price, int N)
{
    LONG R[N + 1]; // table
    for (int i = 0; i <= N; i++)
    {
        R[i] = LONG_MIN;
    }
    return cutRodMemoAux(price, N, R);
}

// Bottom up version
LONG cutRodBottomUp(int *price, int N)
{
    LONG R[N + 1];
    R[0] = 0;
    LONG result;
    for (int j = 1; j <= N; j++)
    {
        result = LONG_MIN;
        for (int i = 1; i <= j; i++)
        {
            result = max(result, (LONG)(price[i - 1] + R[j - i]));
        }
        R[j] = result;
    }
    return R[N];
}

// Optimal Solution
LONG **cutRodBottomUpExtended(int *price, int N)
{
    LONG R[N + 1];
    LONG S[N];
    R[0] = 0;
    LONG **result = (LONG **)malloc(2 * sizeof(LONG *));
    LONG res;
    for (int j = 1; j <= N; j++)
    {
        res = LONG_MIN;
        for (int i = 1; i <= j; i++)
        {
            if (res < price[i - 1] + R[j - i])
            {
                res = price[i - 1] + R[j - i];
                S[j - 1] = (LONG)i;
            }
        }
        R[j] = res;
    }
    result[0] = R;
    result[1] = S;
    return result;
}

void PrintSolution(int *price, int N)
{
    LONG **res;
    res = cutRodBottomUpExtended(price, N);
    while (N > 0)
    {
        printf("%lld\n", res[1][N - 1]);
        N = N - res[1][N - 1];
    }
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N; // Max num of elements
    printf("Enter a integer N:");
    scanf("%d", &N);
    int price[N];
    printf("Enter a array of N integers:\n");
    scanArray(price, N);
    LONG ans;
    // ans = cutRod(price, N); // Naive version
    // ans = cutRodMemo(price, N); // Top-Down Memoized version
    // ans = cutRodBottomUp(price, N); // Bottom Up version
    // printf("%lld\n", ans);
    //PrintSolution(price, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}