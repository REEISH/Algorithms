#include <stdio.h>
#include <time.h>
// Implementation of linear search
void scanArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

int linearSearch(int *A, int start, int end, int NUM)
{
    int j = 0;
    for (int i = start; i <= end; i++)
    {

        if (A[i - 1] == NUM)
        {
            j++;
            return i;
        }
        if (i == end && j == 0)
        {
            return -1;
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
    int Array[N];
    printf("Enter a array of N integers:\n");
    scanArray(Array, N);
    int searchValue;
    printf("Enter a value you want to search int the array:");
    scanf("%d", &searchValue);
    int result = linearSearch(Array, 1, N, searchValue);
    printf("INDEX:%d\nVALUE:%d\nVALUE SEARCHED: %d\n", result, Array[result - 1], searchValue);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}