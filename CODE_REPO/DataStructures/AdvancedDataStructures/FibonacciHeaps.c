#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0

// Use gcc FibonacciHeaps.c -lm to compile
typedef struct FibHeap FHEAP;
typedef struct FibHeap *FHeapPtr;
typedef struct FibNode FNODE;
typedef struct FibNode *FNodePtr;
typedef long long int LONG;
struct FibHeap
{
    int N;        // Number of elements
    FNodePtr Min; // Pointer to the min element of the fib heap
    int Deg;      // Number of elements in Root List
};

struct FibNode
{
    FNodePtr Left;   // Left sibling
    FNodePtr Right;  // Right Sibling
    FNodePtr Parent; // Parent
    FNodePtr Child;  // Child Node
    LONG Value;      // Key
    int Degree;      // No of nodes in child list
    int Mark;        // Has lost child since it became child
};

// Initialising an empty fibonacci heap
FHeapPtr createFibHeap()
{
    FHeapPtr FHeap = (FHeapPtr)malloc(sizeof(FHEAP));
    FHeap->N = 0;
    FHeap->Deg = 0;
    FHeap->Min = NULL;
    return FHeap;
}

// Initialising FIbonaaci Node
FNodePtr initNode(LONG key)
{
    FNodePtr X = (FNodePtr)malloc(sizeof(FNODE));
    if (X == NULL)
    {
        exit(EXIT_FAILURE);
    }
    X->Degree = 0;
    X->Value = key;
    X->Parent = NULL;
    X->Mark = FALSE;
    return X;
}

// Inserting into a empty fibonacci heap
void FibHeapInsert(FHeapPtr FHeap, LONG key)
{
    // Initialising the Node
    FNodePtr X = initNode(key);
    // Adding the node
    if (FHeap->Min == NULL)
    {
        FHeap->Min = X;
        FHeap->Deg = 1;
        X->Left = X;
        X->Right = X;
    }
    else
    {
        X->Right = FHeap->Min;
        X->Left = FHeap->Min->Left;
        FHeap->Min->Left->Right = X;
        FHeap->Min->Left = X;
        if (key < FHeap->Min->Value)
        {
            FHeap->Min = X;
        }
        FHeap->Deg = FHeap->Deg + 1;
    }
    FHeap->N = FHeap->N + 1;
}

// Union of 2 Fibonacci Heaps
// Both Heaps must be non empty
FHeapPtr FibHeapUnion(FHeapPtr FHeap1, FHeapPtr FHeap2)
{
    if (FHeap1 != NULL && FHeap2 != NULL)
    {
        if (FHeap1->Min != NULL && FHeap2->Min != NULL)
        {
            FHeapPtr H = createFibHeap(); // Create new Fibonacci Heap
            H->Min = FHeap1->Min;
            // Concatenation of root lists
            FNodePtr temp = FHeap2->Min->Right;
            FHeap2->Min->Right = H->Min;
            H->Min->Left->Right = temp;
            temp->Left = H->Min->Left;
            H->Min->Left = FHeap2->Min;
            // Update Min Value
            if (FHeap2->Min->Value < FHeap1->Min->Value)
            {
                H->Min = FHeap2->Min;
            }
            H->N = FHeap1->N + FHeap2->N;
            H->Deg = FHeap1->Deg + FHeap2->Deg;
            free(FHeap1);
            free(FHeap2);
            return H;
        }
        else
        {
            if (FHeap1->Min != NULL)
            {
                return FHeap1;
            }
            else
            {
                return FHeap2;
            }
        }
    }
    else
    {
        if (FHeap1 != NULL)
        {
            return FHeap1;
        }
        else
        {
            return FHeap2;
        }
    }
}

// Procedure to implement linking of one FibHeapNode as another Node's child Node
void FibHeapLink(FHeapPtr H, FNodePtr Y, FNodePtr X)
{
    // Remove Y from the root list
    Y->Left->Right = Y->Right;
    Y->Right->Left = Y->Left;
    H->Deg = H->Deg - 1;
    H->Min = X;
    // Add Y to the child's list of X
    if (X->Child != NULL)
    {
        Y->Right = X->Child;
        Y->Left = X->Child->Left;
        X->Child->Left->Right = Y;
        X->Child->Left = Y;
        X->Degree = X->Degree + 1;
        Y->Mark = FALSE;
    }
    else
    {
        X->Child = Y;
        Y->Right = Y;
        Y->Left = Y;
        X->Degree = X->Degree + 1;
        Y->Mark = FALSE;
    }
}

// Procedure to update the root list and concatenate it to make a list of each
// Node having distinct Degrees
void Consolidate(FHeapPtr H)
{
    FNodePtr *A = (FNodePtr *)malloc(((int)(log10(H->N + 1) / log10(2)) + 1) * sizeof(FNodePtr)); // Not optimised space but works in all time
    for (int i = 0; i <= ((int)(log10(H->N + 1) / log10(2))); i++)
    {
        A[i] = NULL;
    }
    FNodePtr temp = H->Min;
    FNodePtr iter = NULL;
    while (iter != H->Min)
    {
        FNodePtr X = temp;
        int D = X->Degree;
        while (A[D] != NULL)
        {
            FNodePtr Y = A[D]; // Another Node with same degree
            if (X->Value > Y->Value)
            {
                FNodePtr Temp = X;
                X = Y;
                Y = Temp;
            }
            FibHeapLink(H, Y, X);
            temp = X;
            A[D] = NULL;
            D = D + 1;
        }
        A[D] = X;
        iter = temp->Left;
        temp = temp->Left;
    }
    H->Min = NULL;
    for (int i = 0; i <= ((int)(log10(H->N + 1) / log10(2))); i++)
    {
        if (A[i] != NULL)
        {
            if (H->Min == NULL)
            {
                // Create root List for H just containing A[i]
                H->Min = A[i];
                A[i]->Left = A[i];
                A[i]->Right = A[i];
            }
            else
            {
                // Add A[i] to H's Root List
                A[i]->Right = H->Min;
                A[i]->Left = H->Min->Left;
                H->Min->Left->Right = A[i];
                H->Min->Left = A[i];
                // Update Min
                if (A[i]->Value < H->Min->Value)
                {
                    H->Min = A[i];
                }
            }
        }
    }
}

// Extract Min in a fibonacci heap
FNodePtr FibHeapExtractMin(FHeapPtr H)
{
    FNodePtr Z = H->Min;
    if (Z != NULL)
    {
        FNodePtr temp;
        while (Z->Child != NULL) // iterating over child's list of Min
        {
            temp = Z->Child;
            if (temp->Left == temp && temp->Right == temp)
            {
                Z->Child = NULL;
            }
            else
            {
                // Updating Child element
                temp->Left->Right = temp->Right;
                temp->Right->Left = temp->Left;
                Z->Child = temp->Left;
            }
            // Updating Z values
            Z->Degree = Z->Degree - 1;
            // Adding child of Min to the root's list
            temp->Right = H->Min;
            temp->Left = H->Min->Left;
            H->Min->Left->Right = temp;
            H->Min->Left = temp;
            H->Deg = H->Deg + 1;
            temp->Parent = NULL;
        }
        // Removing Min from Root's List
        Z->Left->Right = Z->Right;
        Z->Right->Left = Z->Left;
        if (Z == Z->Right || Z == Z->Left)
        {
            H->Min = NULL;
        }
        else
        {
            H->Min = Z->Right;
            Consolidate(H);
        }
        H->N = H->N - 1;
    }
    return Z;
}

// Procedure to remove child of a Node and add it to root List
void Cut(FHeapPtr H, FNodePtr X, FNodePtr Y)
{
    // Removing X from the child list of Y
    if (X->Left == X || X->Right == X || Y->Degree == 1)
    {
        Y->Child = NULL;
        Y->Degree = Y->Degree - 1;
    }
    else
    {
        X->Left->Right = X->Right;
        X->Right->Left = X->Left;
        Y->Degree = Y->Degree - 1;
    }
    // Adding X to the root list of H
    X->Right = H->Min;
    X->Left = H->Min->Left;
    H->Min->Left->Right = X;
    H->Min->Left = X;
    X->Parent = NULL;
    X->Mark = 0;
}

// Recursively check all Nodes in a given branch as per their mark attribute
void CascadingCut(FHeapPtr H, FNodePtr Y)
{
    FNodePtr Z = Y->Parent;
    if (Z != NULL)
    {
        if (Y->Mark == 0)
        {
            Y->Mark = 1;
        }
        else
        {
            Cut(H, Y, Z);
            CascadingCut(H, Z);
        }
    }
}

// Decreasing a key
void FibHeapDecreaseKey(FHeapPtr H, FNodePtr X, LONG Key)
{
    if (Key > X->Value)
    {
        exit(EXIT_FAILURE);
    }
    X->Value = Key;
    FNodePtr Y = X->Parent;
    if (Y != NULL && X->Value < Y->Value)
    {
        Cut(H, X, Y);
        CascadingCut(H, Y);
    }
    if (X->Value < H->Min->Value)
    {
        H->Min = X;
    }
}

// Deleting a Node from a fib heap
FNodePtr FibHeapDelete(FHeapPtr H, FNodePtr X)
{
    FibHeapDecreaseKey(H, X, LONG_MIN);
    FNodePtr DEL = FibHeapExtractMin(H);
    return DEL;
}

// Printing a Fibonacci Heap
void PrintFibHeap(FNodePtr N)
{
    FNodePtr temp = N;
    FNodePtr iter = NULL;
    while (iter != N)
    {
        printf("%lld ", temp->Value);
        if (temp->Child != NULL)
        {
            printf("\nChild List of %lld \n", temp->Value);
            PrintFibHeap(temp->Child);
        }

        iter = temp->Left;
        temp = temp->Left;
    }
    printf("\n");
}

int main()
{
    FHeapPtr H = createFibHeap();
    FHeapPtr U = createFibHeap();
    // Do any operations here
    return 0;
}