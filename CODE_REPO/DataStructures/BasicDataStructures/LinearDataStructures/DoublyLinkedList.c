#include <stdio.h>
#include <stdlib.h>

typedef struct NODE NODE;
typedef struct NODE *NODEpointer;
typedef struct DLL DLList;
typedef struct DLL *DLLpointer;

struct NODE
{
    int key;
    NODEpointer Prev;
    NODEpointer Next;
};

struct DLL // Doubly Linked List
{
    int NUM; // Num of elements
    struct NODE *Root;
};

DLLpointer initList()
{
    DLLpointer List = (DLLpointer)malloc(sizeof(DLList));
    if (List == NULL)
    {
        exit(EXIT_FAILURE);
    }
    List->Root = NULL;
    List->NUM = 0;
    return List;
}

// insert elements at the end
void insert(DLLpointer List, int val)
{
    NODEpointer nod = (NODEpointer)malloc(sizeof(NODEpointer));
    if (nod == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nod->key = val;   // give key value
    nod->Next = NULL; // next is null
    NODEpointer base = List->Root;
    if (base == NULL)
    {
        nod->Prev = NULL;
        base = nod;
        List->Root = nod;
    }
    else
    {
        while (base != NULL)
        {

            if (base->Next == NULL)
            {
                nod->Prev = base;
                base->Next = nod;
                base = NULL;
            }
            else
            {
                base = base->Next;
            }
        }
    }
    List->NUM++;
}
// print elements
void print(DLLpointer List)
{
    NODEpointer base = List->Root;
    while (base != NULL)
    {
        printf("%d ", base->key);
        base = base->Next;
    }
}
// prints the elements in reverse order
void print_reverse(DLLpointer List)
{
    NODEpointer base = List->Root;
    if (List->NUM == 0)
    {
        return;
    }

    while (base->Next != NULL)
    {
        // printf("%d ", base->key);
        base = base->Next;
    }
    while (base != NULL)
    {
        printf("%d ", base->key);
        base = base->Prev;
    }
}
// inserts at a given position i
void insert_at(DLLpointer List, int val, int pos)
{
    NODEpointer nod = (NODEpointer)malloc(sizeof(NODEpointer));
    if (nod == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nod->key = val; // give key value
    NODEpointer base = List->Root;
    if (pos > List->NUM || pos < 0)
    {
        printf("INVALID POSITION");
        exit(EXIT_FAILURE);
    }

    if (pos == 0 && List->NUM != 0)
    {
        List->Root->Prev = nod;
        nod->Next = List->Root;
        List->Root = nod;
        nod->Prev = NULL;
    }
    if (pos == List->NUM || List->NUM == 0)
    {
        insert(List, val);
        List->NUM--;
    }
    for (int i = 0; i < pos + 1; i++)
    {
        if (pos != 0 && pos != List->NUM)
        {
            if (i == pos)
            {
                NODEpointer temp = base->Prev;
                base->Prev = nod;
                temp->Next = nod;
                nod->Prev = temp;
                nod->Next = base;
            }
            base = base->Next;
        }
    }
    List->NUM++;
}
// gets the size of the list
void get_size(DLLpointer List)
{
    printf("%d\n", List->NUM);
}
// deletes the element at given position
void delete (DLLpointer List, int pos)
{
    NODEpointer base = List->Root;
    if (pos == 0)
    {
        if (base == NULL)
        {
            printf("The list is empty");
            exit(EXIT_SUCCESS);
        }
    }
    if (pos > List->NUM || pos < 0)
    {
        printf("INVALID POSITION");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < pos; i++)
    {
        base = base->Next;
    }
    if (base->Prev != NULL && base->Next != NULL)
    {
        base->Prev->Next = base->Next;
        base->Next->Prev = base->Prev;
        free(base);
    }
    if (base->Prev != NULL && base->Next == NULL)
    {
        if (pos == List->NUM - 1)
        {
            base->Prev->Next = NULL;
            free(base);
        }
    }
    if (base->Prev == NULL && base->Next != NULL)
    {
        if (pos == 0)
        {
            base->Next->Prev = NULL;
            List->Root = base->Next;
            free(base);
        }
    }
    if (base->Prev == NULL && base->Next == NULL)
    {
        if (List->NUM == 1 && pos == 0)
        {
            List->Root = NULL;
            free(base);
        }
    }
    List->NUM--;
}
// prunes the list // Deletes element at odd number, note indexing starts at 0
void prune(DLLpointer List)
{
    for (int i = 0; i < List->NUM; i++)
    {
        if (i % 2 == 1)
        {
            delete (List, i);
        }
    }
}

// find an element with a given key k
int find(DLLpointer List, int val)
{
    int i = 0;
    NODEpointer base = List->Root;
    while (base != NULL && i <= List->NUM)
    {
        if (base->key == val)
        {
            return i;
        }
        base = base->Next;
        i++;
    }
    return -1;
}

int main()
{
    DLLpointer List = initList();
    // Do any operation here
    return 0;
}

// To convert into a singly linked list , just remove Prev pointer
// Note the implementation is without the use of sentinals,
// If sentinals are used, it improve the efficiancy of the operations.
// Linked list can also be made using arrays, by keeping indices of previous and next.