// Guass elimination Method
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
// Do NOT dynamically give equations to solve
// Code will give errors
// Point is use Systematic way of giving input ,
// the more the zeroes on the left put the equation in bottom.
typedef long long int LONG;

void scanMatrix(int row, int col, double Matrix[row][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            scanf("%lf", &Matrix[i][j]);
        }
    }
}

void scanArray(double *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%lf", &A[i]);
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

void printMatrix(int row, int col, double Matrix[row][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%lf ", Matrix[i][j]);
        }
        printf("\n");
    }
}

double *GuassElimination(int N, double M[N][N], double *B) // Specific input required
{
    for (int i = 1; i < N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            if (M[i - 1][i - 1] != 0)
            {
                double Coeff = (M[j - 1][i - 1] / M[i - 1][i - 1]);
                for (int k = i; k <= N; k++)
                {
                    M[j - 1][k - 1] = M[j - 1][k - 1] - (Coeff) * (M[i - 1][k - 1]);
                }
                B[j - 1] = B[j - 1] - (Coeff) * (B[i - 1]);
            }
        }
        /*printMatrix(N, N, M);
        printArray(B, N);*/
    }
    for (int i = N; i >= 1; i--)
    {
        int Result = 0;
        for (int j = 1; j <= N; j++)
        {
            if (M[i - 1][j - 1] == 0)
            {
                Result = Result + 1;
            }
        }

        if (Result == N)
        {
            if (B[i - 1] != 0)
            {
                printf("The system has NO solution\n");
            }
            else
            {
                printf("The system has infinitely many solutions\n");
            }
            exit(EXIT_SUCCESS);
        }
    }
    double *X = (double *)malloc(N * sizeof(double));
    for (int i = N; i >= 1; i--)
    {
        double Residue = 0;
        for (int j = i + 1; j <= N; j++)
        {
            Residue = Residue + M[i - 1][j - 1] * X[i];
        }
        X[i - 1] = (B[i - 1] - Residue) / M[i - 1][i - 1];
    }
    return X;
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    LONG N;
    printf("Enter the Num:");
    scanf("%lld", &N);
    double A[N][N];
    printf("Enter the Matrix A:\n");
    scanMatrix(N, N, A);
    double B[N];
    printf("Enter the Matrix B:\n");
    scanArray(B, N);
    // Guass elimination method starts here
    double *X = GuassElimination(N, A, B);
    printArray(X, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}
