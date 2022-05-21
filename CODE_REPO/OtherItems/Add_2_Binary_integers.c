#include <stdio.h>
// This algorithm is only for computing the sum
// of 2 positive numbers written in binary format
// Note that this is just ine way of doing this and other
// apt solutions are also available

void scanArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

int main()
{
    int N;
    printf("Enter a integer N: ");
    scanf("%d", &N);
    int A[N], B[N];
    printf("write down first int in binary: ");
    scanArray(A, N);
    printf("write down second int in binary : ");
    scanArray(B, N);
    int C[N + 1];
    for (int i = 0; i < N + 1; i++)
    {
        C[i] = 0;
    }
    for (int i = N - 1; i >= 0; i--)
    {
        if (A[i] * B[i] == 0)
        {
            C[i + 1] += A[i] + B[i];
        }
        if (A[i] * B[i] == 1)
        {
            C[i + 1] += 0;
            C[i] += 1;
        }
        if (C[i + 1] == 2)
        {
            C[i + 1] = 0;
            C[i] = 1;
        }
    }
    for (int i = 0; i < N + 1; i++)
    {
        printf("%d", C[i]);
    }
    printf("\n");
    return 0;
}