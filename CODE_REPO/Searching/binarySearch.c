#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void scanArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

int binarySearch(int *A, int searchValue, int start, int end)
{
    int mid = (start + end) / 2;
    int ret = -1;
    if (A[mid - 1] == searchValue)
    {
        ret = mid;
        return ret;
    }
    else if (searchValue < A[mid - 1])
    {
        ret = binarySearch(A, searchValue, start, mid - 1);
    }
    else
    {
        ret = binarySearch(A, searchValue, mid + 1, end);
    }

    return ret;
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter a integer N:");
    scanf("%d", &N);
    int Array[N];
    printf("Enter a sorted array N:\n");
    scanArray(Array, N);
    int searchValue;
    printf("Enter a number you want to search :");
    scanf("%d", &searchValue);
    int result;
    result = binarySearch(Array, searchValue, 1, N);
    printf("%d\n", result);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}