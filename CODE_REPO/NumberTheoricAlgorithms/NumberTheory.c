#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define NIL -1

typedef long long int LONG;

// Normal euclid algorithm
// Using Recursive version
LONG Euclid(LONG A, LONG B)
{
    if (A < 0)
    {
        A = -A;
    }
    if (B < 0)
    {
        B = -B;
    }
    if (B == 0)
    {
        return A;
    }
    else
    {
        return Euclid(B, (A % B));
    }
}

// Using Iterative version
LONG EuclidIterative(LONG A, LONG B)
{
    int Temp = 0;
    if (A < 0)
    {
        A = -A;
    }
    if (B < 0)
    {
        B = -B;
    }
    while (B != 0)
    {
        Temp = B;
        B = (A % B);
        A = Temp;
    }
    return A;
}

void PrintArray(LONG *A, LONG N)
{

    for (int i = 0; i < N; i++)
    {
        printf("%lld ", A[i]);
    }
    printf("\n");
}

// To know d  = a*x + b*y for x,y belongs to Z.
LONG *ExtendedEuclid(LONG A, LONG B)
{
    LONG *Res = (LONG *)malloc(3 * sizeof(LONG));
    if (Res == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if (B == 0)
    {
        if (A < 0)
        {
            Res[0] = -A;
            Res[1] = -1;
            Res[2] = 0;
        }
        else
        {
            Res[0] = A;
            Res[1] = 1;
            Res[2] = 0;
        }
        return Res;
    }
    else
    {
        Res = ExtendedEuclid(B, (A % B));
        int Temp = Res[1];
        Res[1] = Res[2];
        Res[2] = Temp - (A / B) * (Res[2]);
        return Res;
    }
}

// Solved ax = b (mod n) where A and N  must be strictly positive
void ModularLinearEquation(LONG A, LONG B, LONG N)
{
    LONG *Res = ExtendedEuclid(A, N);
    if ((B % (Res[0])) == 0)
    {
        LONG *SOLVE = (LONG *)malloc(Res[0] * sizeof(LONG));
        LONG INIT = (Res[1] * (B / Res[0])) % (N);
        if (INIT < 0)
        {
            INIT = (N + INIT) % N; // Though INIT = N + INIT works this one is more cleaner
        }
        for (int i = 0; i < Res[0]; i++)
        {
            SOLVE[i] = (INIT + i * (N / Res[0])) % (N);
        }
        PrintArray(SOLVE, Res[0]);
    }
    else
    {
        printf("No Solution Exists\n");
    }
}

int main()
{
    LONG A, B, N;
    printf("Enter a Number A:");
    scanf("%lld", &A);
    printf("Enter a Number B:");
    scanf("%lld", &B);
    /*printf("Enter a Number N:");
    scanf("%lld", &N);*/
    // LONG Result = Euclid(A, B);
    LONG Result = EuclidIterative(A, B);
    LONG *Res = ExtendedEuclid(A, B);
    printf("Their GCD is :%lld\n", Result);
    printf("Their GCD is :%lld\nCo-efficient of A:%lld\nCo-efficent of B:%lld\n", Res[0], Res[1], Res[2]);
    ModularLinearEquation(A, B, N);
    return 0;
}