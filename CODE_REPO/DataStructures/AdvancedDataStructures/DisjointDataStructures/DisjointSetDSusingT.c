#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

typedef struct DSetNode SET;
typedef struct DSetNode *SPtr;
typedef struct DSetNode SETNODE;
typedef struct DSetNode *SNPtr;

struct DSetNode
{
    SNPtr Parent; // Parent Node
    int Rank;     // Rank
    int Value;    // Value of Node
};

SNPtr initNode(int X)
{
    SNPtr Node = (SNPtr)malloc(sizeof(SETNODE));
    if (Node == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Node->Parent = NULL;
    Node->Value = X;
    Node->Rank = 0;
    return Node;
}

SPtr MakeSet(int X)
{
    SPtr Set = (SPtr)malloc(sizeof(SET));
    if (Set == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Set = initNode(X);
    Set->Parent = Set;
    return Set;
}

// This is a 2-pass-procedure
// The first pass finds the parent of the set
// The second pass updates the parent of each child
SPtr FindSet(SNPtr X)
{
    if (X != X->Parent)
    {
        X->Parent = FindSet(X->Parent);
    }
    else
    {
        return X->Parent;
    }
}

SNPtr Link(SNPtr A, SNPtr B)
{
    if (A->Rank > B->Rank)
    {
        B->Parent = A;
        return A;
    }
    else
    {
        A->Parent = B;
        if (A->Rank == B->Rank)
        {
            B->Rank = B->Rank + 1;
        }
        return B;
    }
}

// Union by both path compression and rank
SPtr UnionByBoth(SNPtr A, SNPtr B)
{
    SPtr Ret = (SPtr)malloc(sizeof(SET));
    if (Ret == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Ret = Link(FindSet(A), FindSet(B));
    return Ret;
}

// Connected components in a graphs
void ConnectedComponents(int *Ver, int *Source, int *Dest, int V, int E)
{
    SPtr *Set = (SPtr *)malloc(V * sizeof(SPtr));
    if (Set == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= V; i++)
    {
        Set[i - 1] = MakeSet(Ver[i - 1]);
    }
    for (int i = 1; i <= E; i++)
    {
        if (FindSet(Set[Source[i - 1] - 1]) != FindSet(Set[Dest[i - 1] - 1]))
        {
            Set[Source[i - 1] - 1] = UnionByBoth(Set[Source[i - 1] - 1], Set[Dest[i - 1] - 1]);
        }
    }
}

int sameComponents(SNPtr A, SNPtr B)
{
    if (FindSet(A) == FindSet(B))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Given an array of all sets it prints a given set
void printSet(SNPtr X, SPtr *ArrSets, int N)
{
    SPtr Set = FindSet(X);
    for (int i = 1; i <= N; i++)
    {
        if (FindSet(ArrSets[i - 1]) == Set)
        {
            printf("%d ", ArrSets[i - 1]->Value);
        }
    }
    printf("\n");
}
// Can improvise complexity of writing by keeping a linked list
// but that has been avoided here
// just to keep difference from the linked list implementation
// and to avoid extra space for linked list

int main(void)
{
    // Sample Code
    /*SPtr *Arr = (SPtr *)malloc(16 * sizeof(SPtr));
    // Need extra space to store union operations unlike
    // linked list implementation overwriting would not work
    // in path compression as we update pointers each time
    SPtr *ArrUnion = (SPtr *)malloc(16 * sizeof(SPtr));
    for (int i = 1; i <= 16; i++)
    {
        Arr[i - 1] = MakeSet(i);
    }
    for (int i = 1; i <= 16; i++)
    {
        printSet(Arr[i - 1], Arr, 16);
    }

    for (int i = 1; i <= 8; i++)
    {
        ArrUnion[i - 1] = UnionByBoth(Arr[i - 1], Arr[i + 7]);
    }

    for (int i = 1; i <= 4; i++)
    {
        ArrUnion[i + 7] = UnionByBoth(Arr[i - 1], Arr[i + 3]);
    }

    for (int i = 1; i <= 2; i++)
    {
        ArrUnion[i + 11] = UnionByBoth(Arr[i - 1], Arr[i + 1]);
    }

    ArrUnion[14] = UnionByBoth(Arr[0], Arr[1]);
    printSet(Arr[0], Arr, 16);*/
    // Do all operations here
    return 0;
}