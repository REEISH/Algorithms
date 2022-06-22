#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#define NIL -1
// Note that in perfect hashing,
// we donot change the keys once stored, so insert all the keys in one go,
// and we donot support any deletion and search takes O(1) time in worst case
// Also we assume that the values are represented in keys only
// so the values are not explicitly handled here
typedef long long int LONG;
typedef struct HashTablePrimary HT;
typedef struct HashTablePrimary *HTptr;
typedef struct HashTableSecondary HTsec;
typedef struct HashTableSecondary *HTsecPtr;
struct HashTablePrimary
{
    int N; // Number of filled spots
    int Size;
    HTsecPtr *ArrayPrim;
};

struct HashTableSecondary
{
    int N;
    int Size;
    int a; // a
    int b; // b
    int *Array;
};

void scanArray(LONG *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%lld", &A[i]);
    }
}

HTptr initHT(int SizeTable)
{
    HTptr HASHTABLE = (HTptr)malloc(sizeof(HT));
    HASHTABLE->N = 0;
    HASHTABLE->Size = SizeTable;
    HASHTABLE->ArrayPrim = (HTsecPtr *)malloc(SizeTable * (sizeof(HTsecPtr)));
    for (int i = 0; i < SizeTable; i++)
    {
        HASHTABLE->ArrayPrim[i] = NULL;
    }
    return HASHTABLE;
}

int HashFunction(LONG key, int p, int a, int b, int m)
{
    // Universal function come into use

    // Hash Function
    int result = ((a * key + b) % (p)) % (m);
    return result;
}

// This is quite a heavyweight function, please improvise this if you can
void InsertAll(HTptr HasHT, LONG *keys, int N)
{
    int AUX[HasHT->Size];
    int NUM[N];
    for (int i = 0; i < N; i++)
    {
        NUM[i] = 0;
    }
    for (int i = 0; i < HasHT->Size; i++)
    {
        AUX[i] = 0;
    }
    for (int i = 1; i <= N; i++)
    {
        int Probe = HashFunction(keys[i - 1], 101, 3, 42, HasHT->Size);
        NUM[i - 1] = Probe;
        AUX[Probe]++;
    }
    for (int i = 0; i < HasHT->Size; i++)
    {
        if (AUX[i] != 0)
        {
            HasHT->ArrayPrim[i] = (HTsecPtr)malloc(sizeof(HTsec));
            HasHT->ArrayPrim[i]->N = AUX[i];
            HasHT->ArrayPrim[i]->Size = AUX[i] * AUX[i];
            //Here is the trickiest part, the next 2 lines are the key
            // to the approach
            HasHT->ArrayPrim[i]->a = 31; // Modify this for no collision
            HasHT->ArrayPrim[i]->b = 47; // Modify this for no collision
            //Currently this wont work for all outputs, neither it is good
            //So modify these 2 lines for no collision in 2nd level.
            HasHT->ArrayPrim[i]->Array = (int *)malloc((AUX[i] * AUX[i]) * sizeof(int));
            for (int j = 0; j < AUX[i] * AUX[i]; i++)
            {
                HasHT->ArrayPrim[i]->Array[j] = NIL;
            }
            for (int j = 0; j < N; j++)
            {
                if (NUM[j] == i)
                {
                    int Probe = HashFunction(keys[j], 101, HasHT->ArrayPrim[i]->a, HasHT->ArrayPrim[i]->b, HasHT->ArrayPrim[i]->Size);
                    if (HasHT->ArrayPrim[i]->Array[Probe] == NIL)
                    {
                        HasHT->ArrayPrim[i]->Array[Probe] = keys[j];
                    }
                }
            }
        }
    }
    HasHT->N = N;
}

int perfectSearch(HTptr HasHT, LONG key)
{
    int Probe = HashFunction(key, 101, 3, 42, HasHT->Size);
    int SecondProbe = HashFunction(key, 101, HasHT->ArrayPrim[Probe]->a, HasHT->ArrayPrim[Probe]->b, HasHT->ArrayPrim[Probe]->Size);
    if (HasHT->ArrayPrim[Probe]->Array[SecondProbe] == NIL)
    {
        return -1;
    }
    else
    {
        if (HasHT->ArrayPrim[Probe]->Array[SecondProbe] == key)
        {
            return 1;
        }
    }
}

int main()
{
    int Size; // Size of the HashTable
    printf("Enter the Size of HashTable:");
    scanf("%d", &Size);
    HTptr HasHT = initHT(Size);
    int N;
    printf("Enter the number of keys(distinct) you want to insert:");
    scanf("%d", &N);
    LONG keys[N];
    printf("Enter the keys here:\n");
    scanArray(keys, N);
    InsertAll(HasHT, keys, N);
    // Do any operations here
    return 0;
}
