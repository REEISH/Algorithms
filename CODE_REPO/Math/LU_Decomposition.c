#include <stdio.h>
#include <stdlib.h>

// Does an LU decomposition of positive or negative definate Square Matrix
void LUDecomposition(float **A, float **L, float **U, int N)
{
    for (int i = 0; i < N; i++)
    {
        U[i][i] = A[i][i];
        for (int j = i + 1; j < N; j++)
        {
            L[j][i] = A[j][i] / U[i][i];
            U[i][j] = A[i][j];
        }
        for (int j = i + 1; j < N; j++)
        {
            for (int k = i + 1; k < N; k++)
            {
                A[j][k] = A[j][k] - L[j][i] * U[i][k];
            }
        }
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    float **A = (float **)malloc(N * sizeof(float *));
    if (A == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < N; i++)
    {
        A[i] = (float *)malloc(N * sizeof(float));
        if (A[i] == NULL)
            exit(EXIT_FAILURE);
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%f", &A[i][j]);
        }
    }
    float **L = (float **)malloc(N * sizeof(float *));
    if (L == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < N; i++)
    {
        L[i] = (float *)malloc(N * sizeof(float));
        if (L[i] == NULL)
            exit(EXIT_FAILURE);
    }
    for (int i = 0; i < N; i++)
        L[i][i] = 1;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
            L[i][j] = 0;
    }
    float **U = (float **)malloc(N * sizeof(float *));
    if (U == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < N; i++)
    {
        U[i] = (float *)malloc(N * sizeof(float));
        if (U[i] == NULL)
            exit(EXIT_FAILURE);
    }
    for (int i = 1; i < N; i++)
    {
        for (int j = i - 1; j >= 0; j--)
            U[i][j] = 0;
    }
    LUDecomposition(A, L, U, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%f ", L[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%f ", U[i][j]);
        }
        printf("\n");
    }
    return 0;
}