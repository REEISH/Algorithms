#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
typedef long long int LONG;

void scanTaskArray(int *A, int *B, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("Enter the start time of task[%d]:", i + 1);
        scanf("%d", &A[i]);
        printf("Enter the end time of task[%d]:", i + 1);
        scanf("%d", &B[i]);
    }
}

int *RecursiveActivitySelector(int *Start, int *End, int start, int end, int *Result)
{
    int M = start + 1;
    int Comparator;
    if (start == 0)
    {
        Comparator = 0;
    }
    else
    {
        Comparator = End[start - 1];
    }
    while (M <= end && Start[M - 1] < Comparator)
    {
        M = M + 1;
    }
    if (M <= end)
    {
        Result[M - 1] = 1;
        return RecursiveActivitySelector(Start, End, M, end, Result);
    }
    else
    {
        return NULL;
    }
}

int *GreedyActivitySelector(int *Start, int *End, int start, int end, int *Result)
{
    Result[0] = 1;
    int K = 1;
    for (int i = 2; i <= end; i++)
    {
        if (Start[i - 1] >= End[K - 1])
        {
            Result[i-1] = 1;
            K = i;
        }
    }
    return Result;
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter the Number of tasks:");
    scanf("%d", &N);
    int TaskStart[N];
    int TaskFinish[N];
    printf("Enter the task in increasing order of finish time:\n");
    scanTaskArray(TaskStart, TaskFinish, N);
    int Result[N];
    for (int i = 0; i < N; i++)
    {
        Result[i] = 0;
    }
    //int *Res = RecursiveActivitySelector(TaskStart, TaskFinish, 0, N, Result);
    int *Res = GreedyActivitySelector(TaskStart, TaskFinish, 0, N, Result);
    for (int i = 0; i < N; i++)
    {
        if (Result[i] == 1)
        {
            printf("Activity [%d] is selected\n", i + 1);
        }
    }
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}