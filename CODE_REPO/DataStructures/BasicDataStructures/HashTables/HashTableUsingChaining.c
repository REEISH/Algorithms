#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
// Use gcc HashTableUsingChaining.c -lm to compile
typedef long long int LONG;
typedef struct HashTable HT;
typedef struct HashTable *HTptr;
typedef struct Head HEAD;
typedef struct Head *Hptr;
typedef struct Node NODE;
typedef struct Node *NODEptr;
typedef struct List LIST;
typedef struct List *LISTptr;
typedef struct ListNode LISTN;
typedef struct ListNode *LISTNptr;
struct HashTable
{
    int M;
    Hptr *Array;
};

struct Head
{
    int NUM;
    NODEptr Root;
};

struct Node
{
    int val;
    LONG key;
    NODEptr Prev;
    NODEptr Next;
};

struct List
{
    LISTNptr Root;
};

struct ListNode
{
    int value;
    LISTNptr Prev;
    LISTNptr Next;
};

HTptr initHT(int Size)
{
    HTptr HashT = (HTptr)malloc(sizeof(HT));
    if (HashT == NULL)
    {
        exit(EXIT_FAILURE);
    }
    HashT->M = Size;
    HashT->Array = (Hptr *)malloc(Size * sizeof(Hptr));
    if (HashT->Array == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < Size; i++)
    {
        HashT->Array[i] = (Hptr)malloc(sizeof(HEAD));
        HashT->Array[i]->NUM = 0;
        HashT->Array[i]->Root = NULL;
    }
    return HashT;
}

LISTptr initList()
{
    LISTptr List = (LISTptr)malloc(sizeof(LIST));
    List->Root = NULL;
    return List;
}

LISTNptr InitListNode(int v)
{
    LISTNptr Nod = (LISTNptr)malloc(sizeof(LISTN));
    Nod->value = v;
    Nod->Prev = NULL;
    Nod->Next = NULL;
    return Nod;
}

void InsertList(LISTptr L, int v /*value*/)
{
    LISTNptr Nod = InitListNode(v);
    if (L->Root == NULL)
    {
        L->Root = Nod;
    }
    else
    {
        LISTNptr temp = L->Root;
        while (temp->Next != NULL)
        {
            temp = temp->Next;
        }
        temp->Next = Nod;
        Nod->Prev = temp;
        Nod->Next = NULL;
    }
}

int HashFunction(HTptr HashT, LONG key /*another argument size of table could be passed*/)
{
    int result;
    // result = h(key);h -> hash function
    // eg h(x) = x%200;

    // result = key % HashT->M; // Division hash function

    // if keys are in range 0<= key<1,
    // we can use result = floor(k*HashT->M);

    // Multiplicative method
    /*float A = 0.618033; // Any value suffices
    result = (int)((float)(HashT->M) * (float)((float)(key * A) - floor(key * A)))*/

    // Universal Hash functions
    // hab(k) = ((a*k + b)mod(p))mod(m).  p>m and p is prime
    // and a belongs to Z(p) = {0,1,.....,p-1}
    // b belongs to Z*(p) = {1,2,3,........,p-1}.
    //Any one of these functions in chosen at random to hash the key to its slots.
    return result;
}

NODEptr InitNode(LONG k /*key*/, int v /*value*/)
{
    NODEptr Nod = (NODEptr)malloc(sizeof(NODE));
    Nod->key = k;
    Nod->val = v;
    Nod->Prev = NULL;
    Nod->Next = NULL;
    return Nod;
}
// Note multiple elemts with the same key value might be inserted, so it
// must be well assumed beforehand that the user has the knowledge of what he/she
// is doing ,so that only one unique value per key is possible
// i.e key ----- value is a function, for one key there exists only one value.
// However this function might not be one to one.
// That a same value might be contained in 2 different keys.
// Hence, search by key strategy is implemented

void ChainedHashInsert(HTptr HashT, LONG key, int val)
{
    NODEptr Nod = InitNode(key, val);
    int Place = HashFunction(HashT, key); // [0 ,Size - 1]
    HashT->Array[Place]->NUM++;
    if (HashT->Array[Place]->Root == NULL)
    {
        HashT->Array[Place]->Root = Nod;
    }
    else
    {
        HashT->Array[Place]->Root->Prev = Nod;
        Nod->Next = HashT->Array[Place]->Root;
        HashT->Array[Place]->Root = Nod;
    }
    // O(1) complexity because it assumes that the element is not already present
}

// Deletion in Hash Table

void ChainedHashDelete(HTptr HashT, int v /*value*/, LONG k /*key*/)
{
    // Delete all instances of that value from the table that match the key
    int Place = HashFunction(HashT, k);
    NODEptr temp = HashT->Array[Place]->Root;
    while (temp != NULL)
    {
        if ((temp->key == k) && (temp->val == v))
        {
            NODEptr del = temp;
            if (del->Prev != NULL)
            {
                del->Prev->Next = del->Next;
            }
            if (del->Next != NULL)
            {
                del->Next->Prev = del->Prev;
            }
            free(del);
            HashT->Array[Place]->NUM--;
        }
        temp = temp->Next;
    } //
    // Note if the same element is passes as a node , deletion takes O(1) time.
    // eg - delete(HTptr HashT,NODEPtr Nod/*Node to be deleted*/)
    // For that we need to keep track of all the nodes added in the table.
    // We can mantain another array for added Nodes.
    // This procedure has been omitted here.
}

// Search for a given key
LISTptr ChainedHashSearch(HTptr HashT, LONG k /*key*/)
{
    int Place = HashFunction(HashT, k);
    LISTptr Result = initList();
    NODEptr temp = HashT->Array[Place]->Root;
    if (temp == NULL)
    {
        return NULL;
    }
    else
    {
        int freq = 0;
        while (temp != NULL)
        {
            if (k == temp->key)
            {
                InsertList(Result, temp->val);
            }
            temp = temp->Next;
        }
        return Result;
    } // it takes O(length of list) time to return in worst case
}

int main()
{
    int Size; // Size of HashTable
    printf("Enter the Size of HashTable:");
    scanf("%d", &Size);
    HTptr HasHT = initHT(Size);
    //Do any operations here
    return 0;
}

// Define hash function yourself or use existing one by removing the comments