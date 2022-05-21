#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
typedef long long int SUM;
typedef long long int *LONG;

void scanArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}
void printArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

LONG maximumCrossingSubarray(int *A, int low, int mid, int high) // 1 to 6 mid 3 0 to 5
{

    int leftSum = INT_MIN;
    int sum = 0;
    int maxLeft = 0;

    for (int i = mid - 1; i >= low - 1; i--)
    {
        sum = sum + A[i];
        if (sum > leftSum)
        {
            leftSum = sum;
            maxLeft = i + 1;
        }
    }
    int rightSum = INT_MIN;
    sum = 0;
    int maxRight = 0;
    for (int i = mid; i <= high - 1; i++)
    {
        sum = sum + A[i];
        if (sum > rightSum)
        {
            rightSum = sum;
            maxRight = i + 1;
        }
    }
    LONG array = (LONG)malloc(3 * sizeof(SUM));
    array[0] = (SUM)maxLeft;
    array[1] = (SUM)maxRight;
    array[2] = (SUM)(leftSum + rightSum);
    return array;
}

LONG maximumSubarray(int *A, int low, int high)
{

    LONG returnArray = (LONG)malloc(3 * sizeof(SUM));
    if (high == low)
    {
        returnArray[0] = (SUM)low;
        returnArray[1] = (SUM)high;
        returnArray[2] = (SUM)A[low - 1];
        return returnArray;
    }
    else
    {
        int mid = (low + high) / 2;

        LONG leftArray = maximumSubarray(A, low, mid);
        LONG rightArray = maximumSubarray(A, mid + 1, high);
        LONG crossingArray = maximumCrossingSubarray(A, low, mid, high);
        if (leftArray[2] >= rightArray[2] && leftArray[2] >= crossingArray[2])
        {
            returnArray = leftArray;
        }
        else if (rightArray[2] >= leftArray[2] && rightArray[2] >= crossingArray[2])
        {
            returnArray = rightArray;
        }
        else
        {
            returnArray = crossingArray;
        }
        return returnArray;
    }
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter a number N:");
    scanf("%d", &N);
    int Array[N];
    scanArray(Array, N);
    LONG result = maximumSubarray(Array, 1, N);
    for (SUM i = result[0] - 1; i <= result[1] - 1; i++)
    {
        printf("%d ", Array[i]);
    }
    printf("\nMax left :%lld\n", result[0]);
    printf("Max right :%lld\n", result[1]);
    printf("Maximum Sum  :%lld\n", result[2]);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}