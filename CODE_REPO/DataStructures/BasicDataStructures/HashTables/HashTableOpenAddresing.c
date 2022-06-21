#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#define DELETED -1
typedef long long int LONG;
typedef struct HashTable HT;
typedef struct HashTable *HTptr;
struct HashTable
{
    int N; // Number of filled spots
    int Size;
    int **Array;
};

HTptr initHT(int SizeTable)
{
    HTptr HASHTABLE = (HTptr)malloc(sizeof(HT));
    HASHTABLE->N = 0;
    HASHTABLE->Size = SizeTable;
    HASHTABLE->Array = (int **)malloc(SizeTable * (sizeof(int *)));
    for (int i = 0; i < SizeTable; i++)
    {
        HASHTABLE->Array[i] = NULL;
    }
    return HASHTABLE;
}

int HashFunctionProbe(HTptr HashT, LONG key, int i)
{
    int result;
    // Hash Function goes here
    int HashVal = (key) % (HashT->Size); // Modify this

    // LinearProbing
    result = (HashVal + /*c*/ i) % (HashT->Size);

    // Quadratic Probing
    // result = (HashVal + /*c1*/ 7 * i + /*c2*/ 17 * (i * i)) % (HashT->Size);

    // Double Hashing
    /*float A = 0.618033;
    int HashFun = (int)((float)(HashT->Size) * (float)((float)(key * A) - floor(key * A)));// Modify this
    result = (HashVal + i * (HashFun)) % (HashT->Size);*/
    return result;
}

void OpenHashInsert(HTptr HashT, LONG key, int val, int HashFunction(HTptr HashT, LONG key, int i))
{
    if (HashT->N == HashT->Size)
    {
        printf("Table Full\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < HashT->Size)
    {
        int Probe = HashFunction(HashT, key, i);
        if (HashT->Array[Probe] == NULL)
        {
            int *temp = (int *)malloc(2 * sizeof(int));
            temp[0] = key;
            temp[1] = val;
            HashT->Array[Probe] = temp;
            HashT->N++;
            return;
        }
        else if ((HashT->Array[Probe])[0] == DELETED)
        {
            (HashT->Array[Probe])[0] = key;
            (HashT->Array[Probe])[1] = val;
            HashT->N++;
        }
        else
        {
            i = i + 1;
        }
    }
}
//To get all the values that belong to the same key, please use a doubly linked list

// Assuming all keys are distinct , it gives the result.
//  If keys are the same or are duplicate, then it gives the first instance of the key.
int OpenHashSearch(HTptr HashT, LONG key, int HashFunction(HTptr HashT, LONG key, int i))
{
    if (key < 0)
    {
        exit(EXIT_FAILURE);
    }
    int i = 0;
    int Probe = HashFunction(HashT, key, i);
    while (i < HashT->Size)
    {
        Probe = HashFunction(HashT, key, i);
        if (HashT->Array[Probe] == NULL)
        {
            return -1;
        }
        else
        {
            if ((HashT->Array[Probe])[0] == key)
            {
                return (HashT->Array[Probe])[1];
            }
            i = i + 1;
        }
    }
}

//it deletes all the instance of the key 
void OpenHashDelete(HTptr HashT, LONG key, int HashFunction(HTptr HashT, LONG key, int i))
{
    if (key < 0)
    {
        exit(EXIT_FAILURE);
    }
    int i = 0;
    int Probe = HashFunction(HashT, key, i);
    while (i < HashT->Size)
    {
        Probe = HashFunction(HashT, key, i);
        if (HashT->Array[Probe] == NULL)
        {
            return;
        }
        else
        {
            if ((HashT->Array[Probe])[0] == key)
            {
                (HashT->Array[Probe])[0] = DELETED;
            }
            i = i + 1;
        }
    }
}

int main()
{
    int Size; // Size of the HashTable
    printf("Enter the Size of HashTable:");
    scanf("%d", &Size);
    HTptr HasHT = initHT(Size);
    // Do any operations here
    return 0;
}
