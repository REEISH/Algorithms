#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void scanArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomPermutation(int *A, int N)
{
    srand(time(NULL));
    for (int i = N - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&A[i], &A[j]);
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
    randomPermutation(array, N);
    printArray(array, N);
    bestCandidate = hireCandidate(array, N);
    printf("\ncandidate %d id the best candidate of all", bestCandidate);
    return 0;
}
