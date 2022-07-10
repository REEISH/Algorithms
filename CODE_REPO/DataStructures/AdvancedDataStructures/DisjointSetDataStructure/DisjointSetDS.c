#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

// Linked List representation
typedef struct List LIST;
typedef struct List *LPtr;
typedef struct LNode LNODE;
typedef struct LNode *LNPtr;

struct List
{
    LNPtr Head; // Head of the list
    LNPtr Tail; // Tail of the list
    int Rep;    // Represenative element
    int Num;    // Number of elements
};

struct LNode
{
    LPtr Head;  // Head of the list
    int value;  // value of the node
    LNPtr Prev; // Previous element
    LNPtr Next; // Next element
};

LNPtr initNode(int X)
{
    LNPtr Node = (LNPtr)malloc(sizeof(LNODE));
    if (Node == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Node->Head = NULL;
    Node->Prev = NULL;
    Node->Next = NULL;
    Node->value = X;
    return Node;
}

LPtr MakeSet(int X)
{
    LPtr Set = (LPtr)malloc(sizeof(LIST));
    if (Set == NULL)
    {
        exit(EXIT_FAILURE);
    }
    LNPtr Node = initNode(X);
    Set->Head = Node;
    Set->Tail = Node;
    Set->Num = 1;
    Set->Rep = X;
    Node->Head = Set;
    return Set;
}

LPtr FindSet(LNPtr X)
{
    return X->Head;
}

int FindSetRep(LNPtr X)
{
    return X->Head->Rep;
}

// Union by rank
LPtr UnionbyRank(LPtr A, LPtr B)
{
    if (A != NULL && B != NULL)
    {
        if (A->Num >= B->Num)
        {
            LNPtr temp = B->Head;
            temp->Prev = A->Tail;
            A->Tail->Next = temp;
            while (temp != NULL)
            {
                temp->Head = A;
                temp = temp->Next;
            }
            A->Tail = B->Tail;
            free(B);
            return A;
        }
        else
        {
            LNPtr temp = A->Head;
            temp->Prev = B->Tail;
            B->Tail->Next = temp;
            while (temp != NULL)
            {
                temp->Head = B;
                temp = temp->Next;
            }
            B->Tail = A->Tail;
            free(A);
            return B;
        }
    }
    else if (A == NULL)
    {
        return B;
    }
    else if (B == NULL)
    {
        return A;
    }
}

void printSet(LPtr A)
{
    if (A == NULL)
    {
        exit(EXIT_FAILURE);
    }
    LNPtr temp = A->Head;
    while (temp != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->Next;
    }
    printf("\n");
}
// Linked List implementation ends here
void ConnectedComponents(int *Ver, int *Source, int *Dest, int V, int E)
{
    LPtr *Set = (LPtr *)malloc(V * sizeof(LPtr));
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
            Set[Source[i - 1] - 1] = UnionbyRank(Set[Source[i - 1] - 1], Set[Dest[i - 1] - 1]);
        }
    }
}

int sameComponents(LPtr A, LPtr B)
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

int main()
{
    //  Sample Code
    /*LPtr *Arr = (LPtr *)malloc(16 * sizeof(LPtr));
    for (int i = 1; i <= 16; i++)
    {
        Arr[i - 1] = MakeSet(i);
    }
    for (int i = 1; i <= 8; i++)
    {
        Arr[i - 1] = UnionbyRank(Arr[i - 1], Arr[i + 7]);
    }
    for (int i = 1; i <= 4; i++)
    {
        Arr[i - 1] = UnionbyRank(Arr[i - 1], Arr[i + 3]);
    }
    for (int i = 1; i <= 2; i++)
    {
        Arr[i - 1] = UnionbyRank(Arr[i - 1], Arr[i + 1]);
    }
    Arr[0] = UnionbyRank(Arr[0], Arr[1]);
    printSet(Arr[0]);*/
    // Do all operations here
    return 0;
}
