#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
// for decimals between 0 and 1 strictly  between
typedef struct Node NODE;
typedef struct Node *NODEptr;

struct Node
{
    float Value;
    NODEptr Prev;
    NODEptr Next;
};
void scanArray(float *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%f", &A[i]);
    }
}

void printArray(float *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%.4f ", A[i]);
    }
    printf("\n");
}

NODEptr first(NODEptr *B, int nParts)
{
    int i = 0;
    while (i < nParts && B[i] == NULL)
    {
        i++;
    }
    return B[i];
}

void insertionSort(NODE *headNode, NODE *lastNode)
{
    if ((headNode == NULL) || (headNode == lastNode))
    {
        return;
    }
    else
    {
        NODE *temp;
        temp = headNode->Next; // i = 1
        while (temp != NULL)
        {
            NODE *StartNode = temp->Next; // Iteration starter equival;ent to i=i+1 for array
            float key = temp->Value;
            while ((temp->Prev != NULL) && (temp->Prev->Value > key))
            {
                temp->Value = temp->Prev->Value;
                temp = temp->Prev;
            }
            temp->Value = key;
            temp = StartNode;
        }
        return;
    }
}

int BucketVal(float NUM, int nParts)
{
    return (NUM)*nParts;
}

void bucketSort(float *A, float *R, int N, int nParts)
{
    NODE *B[nParts];
    NODE *Last[nParts];
    for (int i = 0; i < nParts; i++)
    {
        B[i] = NULL;
        Last[i] = NULL;
    }

    for (int i = 0; i < N; i++)
    {
        NODEptr InsertNode = (NODEptr)malloc(sizeof(NODE));
        InsertNode->Value = A[i];
        InsertNode->Prev = NULL;
        InsertNode->Next = NULL;
        if (B[BucketVal(A[i], nParts)] == NULL)
        {
            B[BucketVal(A[i], nParts)] = InsertNode;
            Last[BucketVal(A[i], nParts)] = InsertNode;
        }
        else
        {
            InsertNode->Prev = Last[BucketVal(A[i], nParts)];
            InsertNode->Next = NULL;
            Last[BucketVal(A[i], nParts)]->Next = InsertNode;
            Last[BucketVal(A[i], nParts)] = InsertNode;
        }
    }
    for (int i = 0; i < nParts; i++)
    {
        insertionSort(B[i], Last[i]);
    }
    NODE *ListHead;
    ListHead = first(B, nParts);

    int LastList = 0;
    int CurrentList = 0;
    for (int i = 0; i < nParts - 1; i++)
    {
        if (B[i] == NULL)
        {
            continue;
        }
        LastList = i;

        while (B[i + 1] == NULL && i < nParts - 1)
        {
            i++;
        }
        CurrentList = i + 1;

        if (CurrentList < nParts)
        {
            Last[LastList]->Next = B[CurrentList];
        }
    }

    int j = 0;
    NODE *temp = ListHead;
    while (temp != NULL)
    {
        R[j] = temp->Value;
        temp = temp->Next;
        j++;
    }
}

int main()
{
    clock_t clockTime;
    clockTime = clock();
    int N;
    printf("Enter a integer N:\n");
    scanf("%d", &N);
    int nParts;
    printf("Enter a integer k(Number of buckets you want):");
    scanf("%d", &nParts);
    float Array[N];
    float Result[N];
    printf("Enter the array:\n");
    scanArray(Array, N);
    bucketSort(Array, Result, N, nParts);
    printArray(Result, N);
    clockTime = clock() - clockTime;
    printf("Time taken in execution :%f\n ", ((double)clockTime) / CLOCKS_PER_SEC);
    return 0;
}

// The indexing of C arrays is done to make sure the output is right