#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <omp.h>
#include <time.h>
#include <limits.h>

// Code For Multithread Fibonaaci
typedef long long int LONG;

LONG FibMT(int N)
{
    if (N < 0)
        exit(EXIT_FAILURE);
    if (N == 1)
        return 1;
    if (N == 0)
        return 0;
    LONG X = FibMT(N - 1);
    LONG Y;
#pragma omp parallel
    {
        Y = FibMT(N - 2);
    }
    return X + Y;
}

LONG Fib(int N)
{
    if (N < 0)
        exit(EXIT_FAILURE);
    if (N == 1)
        return 1;
    if (N == 0)
        return 0;
    LONG X = Fib(N - 1);
    LONG Y = Fib(N - 2);
    return X + Y;
}

int DotProduct(int *X, int *Y, int L, int H)
{
    if (L == H)
    {
        return X[0] * Y[0];
    }
    int M = (L + H) / 2;
    int A, B;
    A = DotProduct(X, Y, L, M);
#pragma omp parallel
    {
        B = DotProduct(X, Y, M + 1, H);
    }
    return A + B;
}

int **MatMultiply(int **A, int **B, int P, int Q, int R)
{
    int **C = (int **)malloc(P * sizeof(int *));
    if (C == NULL)
        exit(EXIT_FAILURE);
#pragma omp parallel
    {
        for (int i = 0; i < P; i++)
        {
            C[i] = (int *)malloc(R * sizeof(int));
            if (C[i] == NULL)
                exit(EXIT_FAILURE);
        }
    }
#pragma parallel
    {
        for (int i = 0; i < P; i++)
        {
#pragma omp parallel
            {
                for (int j = 0; j < R; j++)
                {
                    C[i][j] = DotProduct(A[i], B[j], 1, Q);
                }
            }
        }
    }
    return C;
}

int *MatVec(int **A, int N_Row, int N_Col, int *X)
{
    int *Y = (int *)malloc(N_Row * sizeof(int));
    if (Y == NULL)
        exit(EXIT_FAILURE);
#pragma omp parallel for
    {
        for (int i = 0; i < N_Row; i++)
            Y[i] = 0;
    }
#pragma omp parallel for
    {
        for (int i = 0; i < N_Row; i++)
        {
            for (int j = 0; j < N_Col; j++)
                Y[i] = Y[i] + A[i][j] * X[j];
        }
    }
    return Y;
}

// Multithreaded MergeSort

int BinarySearch(int X, int *T, int S, int E)
{
    int L = S;
    int H;
    if (S > E + 1)
        H = S;
    else
    {
        H = E + 1;
    }
    while (L < H)
    {
        int M = (L + H) / 2;
        if (X <= T[M - 1])
        {
            H = M;
        }
        else
        {
            L = M + 1;
        }
    }
    return H;
}

void Merge(int *T, int S1, int E1, int S2, int E2, int *B, int P)
{
    int L1 = E1 - S1 + 1;
    int L2 = E2 - S2 + 1;
    if (L1 < L2)
    {
        int T1, T2, T3;
        T1 = S2;
        S2 = S1;
        S1 = T1;
        T2 = E2;
        E2 = E1;
        E1 = T2;
        T3 = L2;
        L2 = L1;
        L1 = T3;
    }
    if (L1 == 0)
        return;
    else
    {
        int Q1 = (S1 + E1) / 2;
        int Q2 = BinarySearch(T[Q1 - 1], T, S2, E2);
        int Q3 = P + (Q1 - S1) + (Q2 - S2);
        B[Q3 - 1] = T[Q1 - 1];
#pragma omp parallel
        {
            Merge(T, S1, Q1 - 1, S2, Q2 - 1, B, P);
        }
        Merge(T, Q1 + 1, E1, Q2, E2, B, Q3 + 1);
    }
}

void MergeSort(int *A, int *B, int S, int E, int P)
{
    int L = E - S + 1;
    if (L == 1)
        B[P - 1] = A[S - 1];
    else
    {
        // int T[L];
        int *T = (int *)malloc(L * sizeof(int));
        if (T == NULL)
            exit(EXIT_FAILURE);
        int Q = (S + E) / 2;
        int QP = Q - S + 1;
#pragma omp parallel
        {
            MergeSort(A, T, S, Q, 1);
        }
        MergeSort(A, T, Q + 1, E, QP + 1);
        Merge(T, 1, QP, QP + 1, L, B, P);
    }
}

void merge(int *A, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1 + 1];
    int R[n2 + 1];
    for (int i = 0; i < n1; i++)
    {
        L[i] = A[p + i - 1];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = A[q + i];
    }
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i = 0;
    int j = 0;
    for (int k = p - 1; k < r; k++)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i = i + 1;
        }
        else
        {
            A[k] = R[j];
            j = j + 1;
        }
    }
}

void mergeSort(int *A, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(A, start, mid);
        mergeSort(A, mid + 1, end);
        merge(A, start, mid, end);
    }
}

int main()
{
    /*int N;
    scanf("%d", &N);
    clock_t T = clock();
    LONG MTF = FibMT(N);
    T = clock() - T;
    printf("%f %lld\n", ((double)T) / CLOCKS_PER_SEC, FibMT(N));
    T = clock();
    LONG F = Fib(N);
    T = clock() - T;
    printf("%f %lld\n", ((double)T) / CLOCKS_PER_SEC, Fib(N));
    int N_Row, N_Col;
    scanf("%d %d", &N_Row, &N_Col);
    int **A = (int **)malloc(N_Row * sizeof(int *));
    if (A == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < N_Row; i++)
    {
        A[i] = (int *)malloc(N_Col * sizeof(int));
        if (A[i] == NULL)
            exit(EXIT_FAILURE);
    }
    int *X = (int *)malloc(N_Col * sizeof(int));
    if (X == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < N_Row; i++)
    {
        for (int j = 0; j < N_Col; j++)
            scanf("%d", &A[i][j]);
    }
    for (int i = 0; i < N_Col; i++)
        scanf("%d", &X[i]);
    int *Y = MatVec(A, N_Row, N_Col, X);
    for (int i = 0; i < N_Col; i++)
        printf("%d ", Y[i]);
    printf("\n");
    int P, Q, R;
    scanf("%d %d %d", &P, &Q, &R);
    int **C = (int **)malloc(P * sizeof(int *));
    if (C == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < P; i++)
    {
        C[i] = (int *)malloc(Q * sizeof(int));
        if (C[i] == NULL)
            exit(EXIT_FAILURE);
    }
    int **D = (int **)malloc(Q * sizeof(int *));
    if (D == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < Q; i++)
    {
        D[i] = (int *)malloc(R * sizeof(int));
        if (D[i] == NULL)
            exit(EXIT_FAILURE);
    }
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < Q; j++)
            scanf("%d", &C[i][j]);
    }
    for (int i = 0; i < Q; i++)
    {
        for (int j = 0; j < R; j++)
            scanf("%d", &D[i][j]);
    }
    int **Z = MatMultiply(C, D, P, Q, R);
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            printf("%d ", Z[i][j]);
        }
        printf("\n");
    }*/
    /*int Num;
    scanf("%d", &Num);
    int AN[Num];
    for (int i = 0; i < Num; i++)
    {
        scanf("%d", &AN[i]);
    }
    int B[Num];
    MergeSort(AN, B, 1, Num, 1);
    for (int i = 0; i < Num; i++)
    {
        printf("%d ", B[i]);
    }
    printf("\n");
    clock_t T;
    float MT[1000];
    float TN[1000];
    for (int i = 0; i < 1000; i++)
    {
        int A[2 * i + 2];
        int BX[2 * i + 2];
        for (int j = 0; j < 2 * i + 2; j++)
        {
            A[j] = 2 * i + 2 - 2 * j;
        }
        T = clock();
        MergeSort(A, BX, 1, 2 * i + 2, 1);
        T = clock() - T;
        MT[i] = ((double)T) / CLOCKS_PER_SEC;
        T = clock();
        mergeSort(A, 1, 2 * i + 2);
        T = clock() - T;
        TN[i] = ((double)T) / CLOCKS_PER_SEC;
    }
    for (int i = 0; i < 1000; i++)
    {
        printf("%f ", MT[i] / TN[i]);
    }
    printf("\n");*/
    return 0;
}
