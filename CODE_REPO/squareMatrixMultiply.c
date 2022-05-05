#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
void scanMatrix(int row, int col, int Matrix[row][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            scanf("%d", &Matrix[i][j]);
        }
    }
}
void printMatrix(int row, int col, int Matrix[row][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ", Matrix[i][j]);
        }
        printf("\n");
    }
}
void MartixMultiply(int N, int Matrix1[N][N], int Matrix2[N][N], int Result[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Result[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                Result[i][j] = Result[i][j] + (Matrix1[i][k] * Matrix2[k][j]);
            }
        }
    }
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter a integer N:");
    scanf("%d", &N);
    int Result[N][N];
    int Matrix1[N][N];
    int Matrix2[N][N];
    printf("Scan Matrix1 :\n");
    scanMatrix(N, N, Matrix1);
    printf("Scan Matrix2 :\n");
    scanMatrix(N, N, Matrix2);
    MartixMultiply(N, Matrix1, Matrix2, Result);
    printf("\n");
    printf("Resulted Matrix after multiplication :\n");
    printMatrix(N, N, Result);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}
