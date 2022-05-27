#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
typedef struct interval INTERVAL;
struct interval
{
    int startNum;
    int endNum;
    int Index;
};
void scanStructArray(INTERVAL *I, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("Enter the %d interval\n", i + 1);
        printf("Enter the Start value:");
        scanf("%d", &I[i].startNum);
        printf("Enter the ending value:");
        scanf("%d", &I[i].endNum);
        if (I[i].startNum > I[i].endNum)
        {
            printf("INVALID INPUT\n");
            exit(EXIT_FAILURE);
        }
        I[i].Index = i + 1;
    }
}

void printStructArray(INTERVAL *I, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", I[i].Index);
    }
    printf("\n");
}

void swap(INTERVAL *a, INTERVAL *b)
{
    INTERVAL temp = *a;
    *a = *b;
    *b = temp;
}

int isLessThan(INTERVAL *a, INTERVAL *b)
{
    if (a->endNum < b->startNum)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isIntersecting(INTERVAL *a, INTERVAL *b)
{
    if (b->startNum <= a->endNum && b->endNum >= a->startNum)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int *partition(INTERVAL *I, int start, int end)
{
    int *result = (int *)malloc(2 * sizeof(int));
    INTERVAL pivot = I[end - 1]; // using last element as pivot

    int i = start - 1; // Element shorter than pivot
    int Length = 0;    // Element equal to pivot

    // while start ------- end if element is less than pivot swap to it's left
    for (int j = start; j <= end - 1; j++)
    {
        if (isLessThan(&I[j - 1], &pivot))
        {
            i++; // increase
            if (i + Length < j)
            {
                swap(&I[i + Length - 1], &I[i - 1]); // At the end remove and replace
                swap(&I[i - 1], &I[j - 1]);          // Swap as normal partition does
            }
            else if ((i + Length) == j)
            {
                swap(&I[j - 1], &I[i - 1]);
            }
        }
        else if (isIntersecting(&I[j - 1], &pivot)) // If equal to pivot
        {
            Length++;                            // Length increases
            swap(&I[j - 1], &I[i + Length - 1]); // Swap to length
        }
    }

    swap(&I[i + Length], &I[end - 1]); // the end element
    result[0] = i + 1;                 // Element shorter than pivot + 1
    result[1] = i + Length;            // Element larger than pivot - 1

    return result;
}

// Overlapping intervals are considered to be the same elements
void fuzzySort(INTERVAL *I, int start, int end)
{
    int *parter; // partingElement
    if (start < end)
    {
        parter = partition(I, start, end);

        fuzzySort(I, start, parter[0] - 1);
        fuzzySort(I, parter[1] + 1, end);
    }
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter a integer N:");
    scanf("%d", &N);
    INTERVAL *Interval;
    Interval = (INTERVAL *)malloc(N * sizeof(INTERVAL));
    for (int i = 0; i < N; i++)
    {
        Interval[i].startNum = 0;
        Interval[i].endNum = 0;
        Interval[i].Index = -1;
    }
    printf("Enter the intervals:\n");
    scanStructArray(Interval, N);
    fuzzySort(Interval, 1, N);
    printStructArray(Interval, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}

// For now, the intervals are kept as integers
// but they can be changed to float/double, as pwer the need.