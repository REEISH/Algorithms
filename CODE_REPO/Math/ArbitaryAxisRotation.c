#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
void printMatrix(int row, int col, double Matrix[row][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%f ", Matrix[i][j]);
        }
        printf("\n");
    }
}

void MartixMultiply(int N, int M, int K, double Matrix1[N][M], double Matrix2[M][K], double Result[N][K])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < K; j++)
        {
            Result[i][j] = 0;
            for (int L = 0; L < M; L++)
            {
                Result[i][j] = Result[i][j] + (Matrix1[i][L] * Matrix2[L][j]);
            }
        }
    }
}

void Transpose(int row, int col, double Matrix[row][col], double Result[col][row])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            Result[i][j] = Matrix[j][i];
        }
    }
}

void GenerateRotatorMatrix(double *N, double Matrix[3][3])
{
    if (N[0] == 0 && N[1] == 0)
    {
        Matrix[0][0] = 1;
        Matrix[0][1] = 0;
        Matrix[0][2] = 0;
        Matrix[1][0] = 0;
        Matrix[1][1] = 1;
        Matrix[1][2] = 0;
        Matrix[2][0] = 0;
        Matrix[2][1] = 0;
        Matrix[2][2] = 1;
        return;
    }
    double SumZ = 0;
    double SumX = 0;
    double SumY = 0;
    for (int i = 0; i < 3; i++)
    {
        SumZ = SumZ + N[i] * N[i];
    }
    for (int i = 0; i < 2; i++)
    {
        SumX = SumX + N[i] * N[i];
    }
    SumX = sqrt(SumX);
    SumZ = sqrt(SumZ);
    SumY = SumX * SumZ;
    for (int i = 0; i < 3; i++)
    {
        Matrix[2][i] = N[i] / SumZ;
    }

    Matrix[0][0] = -N[1] / SumX;
    Matrix[0][1] = N[0] / SumX;
    Matrix[0][2] = 0;
    Matrix[1][0] = -(N[0] * N[2]) / SumY;
    Matrix[1][1] = -(N[1] * N[2]) / SumY;
    Matrix[1][2] = (N[0] * N[0] + N[1] * N[1]) / SumY;
}

void Rotation(double Angle, double Matrix[3][3])
{
    Matrix[0][0] = cos(Angle * M_PI / 180);
    Matrix[0][1] = -sin(Angle * M_PI / 180);
    Matrix[0][2] = 0;
    Matrix[1][0] = sin(Angle * M_PI / 180);
    Matrix[1][1] = cos(Angle * M_PI / 180);
    Matrix[1][2] = 0;
    Matrix[2][0] = 0;
    Matrix[2][1] = 0;
    Matrix[2][2] = 1;
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    double Axis[3];
    printf("Enter an arbitary axis Direction Ratios:\n");
    scanArray(Axis, 3);
    double Point[3][1];
    printf("Enter a point to be rotated:\n");
    scanMatrix(3, 1, Point);
    double Angle;
    printf("Enter the angle(in degrees) by which the point is rotated:\n");
    scanf("%lf", &Angle);
    double Result[3][1];
    double Matrix1[3][3];
    double Matrix2[3][3];
    double ResultFinal[3][1];
    double Rotate[3][3];
    double Output[3][1];
    GenerateRotatorMatrix(Axis, Matrix1);
    Transpose(3, 3, Matrix1, Matrix2);
    Rotation(Angle, Rotate);
    MartixMultiply(3, 3, 1, Matrix1, Point, Result);
    MartixMultiply(3, 3, 1, Rotate, Result, ResultFinal);
    MartixMultiply(3, 3, 1, Matrix2, ResultFinal, Output);
    printMatrix(3, 1, Output);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}