#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
// Assuming the range of keys is  0 to 10^6-1
typedef struct HashTable HT;
typedef struct HashTable *HTptr;
struct HashTable
{
    int N; // Number of filled spots
    int *Array[1000000];
};

HTptr initHT()
{
    HTptr HASHTABLE = (HTptr)malloc(sizeof(HT));
    HASHTABLE->N = 0;
    for (int i = 0; i < 1000000; i++)
    {
        HASHTABLE->Array[i] = NULL;
    }
    return HASHTABLE;
}

void DirectInsert(HTptr HashT, int key, int val)
{
    if (HashT->Array[key] == NULL)
    {
        int *temp = (int *)malloc(sizeof(int));
        *temp = val;
        HashT->Array[key] = temp;
        HashT->N++;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

void DirectDelete(HTptr HashT, int key)
{
    if (HashT->Array[key] != NULL)
    {
        free(HashT->Array[key]);
        HashT->Array[key] = NULL;
        HashT->N--;
    }
}

int DirectSearch(HTptr HashT, int key)
{
    if (HashT->Array[key] != NULL)
    {
        int *val = HashT->Array[key];
        return *val;
    }
    else
    {
        return -1;
    }
}

int main()
{
    HTptr HasHT = initHT();
    // Do any operations here
    return 0;
}
