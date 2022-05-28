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

void printSolution(int N, LONG S[N - 1][N - 1], int i, int j)
{
    if (i == j)
    {
        printf("A[%d]", i);
    }
    else
    {
        printf("(");
        printSolution(N, S, i, S[i - 1][j - 2]);
        printSolution(N, S, S[i - 1][j - 2] + 1, j);
        printf(")");
    }
}

void matrixChainOrder(int *order, int N)
{
    LONG M[N][N];
    LONG S[N - 1][N - 1];

    LONG res;
    for (int i = 1; i <= N; i++)
    {
        M[i - 1][i - 1] = 0;
    }
    for (int L = 2; L <= N; L++)
    {
        for (int i = 1; i <= N - L + 1; i++)
        {
            int j = i + L - 1;
            M[i - 1][j - 1] = LONG_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                res = M[i - 1][k - 1] + M[k][j - 1] + order[i - 1] * order[k] * order[j];
                if (res < M[i - 1][j - 1])
                {
                    M[i - 1][j - 1] = res;
                    S[i - 1][j - 2] = k;
                }
            }
        }
    }
    printf("COST:%lld\n", M[0][N - 1]);
    printSolution(N, S, 1, N);
    printf("\n");
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N; // Max num of elements
    printf("Enter a integer N:");
    scanf("%d", &N);
    int order[N + 1];
    printf("Enter a array of N+1 integers:\n");
    scanArray(order, N + 1);
    matrixChainOrder(order, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}