#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Gives a Random value between [0,1)
float Random01()
{
    int A[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    float X = 0;
    for (int i = 1; i <= 10; i++)
    {
        int Y = clock();
        int t = i;
        while (t > 0)
        {
            Y = Y % A[t - 1];
            t--;
        }
        X = X + Y * pow(2, -i);
    }
    return X;
}

int Rand()
{
    float X = Random01();
    if (X < 0.5000)
        return 0;
    else
        return 1;
}

// Gives false with a/b probability and true with 1 - a/b probability assume a < b
int RandomBiased(float a, float b)
{
    if (a == b)
        return 0;
    if (a > b)
    {
        float X = a;
        a = b;
        b = X;
    }
    float D = a / b;
    int A[32];
    float X = D;
    for (int i = 0; i < 32; i++)
        A[i] = -1;
    for (int i = 0; i < 32; i++)
    {
        X = 2 * X;
        if (X > 1)
        {
            A[i] = 1;
            X = X - 1;
        }
        else
        {
            A[i] = 0;
        }
    }
    for (int i = 0; i < 32; i++)
    {
        int X = Rand();
        if (X != A[i])
        {
            if (X > A[i])
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

// Gives a Random value between [a,b)
float RandomAB(float A, float B)
{
    return (A + B) / 2 + (Random01() - 0.5) * (B - A);
}

// Choose a Random Integer between A(inclusive) and B (exclusive)
int RandomI(int A, int B)
{
    return (int)RandomAB((float)A, (float)B);
}

void swap(int *A, int *B)
{
    int T = *B;
    *B = *A;
    *A = T;
}

void RandomiseInPlace(int *A, int N)
{
    for (int i = 0; i < N; i++)
        swap(&A[i], &A[RandomI(i, N)]);
}

int main()
{
    int C0 = 0;
    int C1 = 0;
    for (int i = 0; i < 10000; i++)
    {
        int X = RandomBiased(1, 2);
        // printf("%d\n", X);
        if (X == 0)
            C0++;
        if (X == 1)
            C1++;
    }
    printf("%d %d\n", C0, C1);
    int A[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 10000; i++)
    {
        int X = RandomI(1, 10);
        A[X - 1]++;
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
    int X[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    RandomiseInPlace(X, 10);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", X[i]);
    }
    printf("\n");
    return 0;
}