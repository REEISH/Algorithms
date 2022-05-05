#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
typedef long long int SUM;
typedef long long int *LONG;

void scanArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
}
void printArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

LONG maximalSubarrayLinearTime(int *Array, int N)
{
    LONG result = (LONG)malloc(3 * sizeof(SUM));
    SUM maxLeft;
    SUM maxRight;
    SUM crossingSUM = 0;
    SUM Left = 1;
    SUM maximumSUM = INT_MIN;

    for (int i = 0; i < N; i++)
    {
        crossingSUM = crossingSUM + Array[i];
        if (crossingSUM > maximumSUM)
        {
            maxLeft = Left;
            maxRight = i + 1;
            maximumSUM = crossingSUM;
        }
        if (crossingSUM < 0)
        {
            crossingSUM = 0;
            Left = i + 2;
        }
    }
    result[0] = maxLeft;
    result[1] = maxRight;
    result[2] = maximumSUM;
    return result;
}

void main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter a number N:");
    scanf("%d", &N);
    int Array[N];
    scanArray(Array, N);
    LONG result = maximalSubarrayLinearTime(Array, N);
    for (SUM i = result[0] - 1; i <= result[1] - 1; i++)
    {
        printf("%d ", Array[i]);
    }
    printf("\nMax left :%lld\n", result[0]);
    printf("Max right :%lld\n", result[1]);
    printf("Maximum Sum  :%lld\n", result[2]);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
}