#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void scanArray(int *A, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
}
int hireCandidate(int *A, int N)
{
    int best = 1;
    printf("candidate %d is hired", best);
    for (int i = 1; i < N; i++)
    {
        if (A[i] > A[best - 1])
        {
            best = i + 1;
            printf("\ncandidate %d is hired", best);
        }
    }
    return best;
}

int main()
{
    int N;
    int bestCandidate;
    printf("Enter number of candidates :");
    scanf("%d", &N);
    int array[N];
    scanArray(array, N);
    bestCandidate = hireCandidate(array, N);
    printf("\ncandidate %d id the best candidate of all", bestCandidate);
}
