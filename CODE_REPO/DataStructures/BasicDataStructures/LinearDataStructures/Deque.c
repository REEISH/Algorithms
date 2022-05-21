#include <stdio.h>
#include <stdlib.h>

typedef struct dequeue Dequeue;
typedef struct dequeue* DequeuePointer;
typedef long long int ElementType;
typedef long int Size;
typedef long long int LONG;
struct dequeue
{
    long int n; // size of dequeue
    ElementType array[100000];
};

// Initialise the dequeue
DequeuePointer initDequeue()
{
    DequeuePointer dequeue = (DequeuePointer)malloc(sizeof(Dequeue));
    if (dequeue == NULL)
    {
        exit(EXIT_FAILURE);
    }
    dequeue->n = 0;
    for (int i = 0; i < 100000; i++)// 10 to the power 6
    {
        dequeue->array[i] = 0;
    }
    return dequeue;
}

ElementType popFront(DequeuePointer dequeue)
{
    if (dequeue != NULL) // dequeue exists
    {
        if (dequeue->n != 0) // has some elements in it
        {
            ElementType ret = dequeue->array[0];
            Size s = 0;
            while (s < dequeue->n)
            {
                dequeue->array[s] = dequeue->array[s + 1];
                s++;
            } // shifting the array left
            // dequeue->array[dequeue->n - 1] = 0;
            dequeue->n--;
            return ret;
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

ElementType popBack(DequeuePointer dequeue)
{
    if (dequeue != NULL)
    {
        if (dequeue->n != 0)
        {
            ElementType ret = dequeue->array[dequeue->n - 1];
            dequeue->n--;

            return ret;
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

void pushFront(DequeuePointer dequeue, ElementType elem)
{
    if (dequeue != NULL)
    {
        if (dequeue->n > 0)
        {
            Size temp = dequeue->n;

            for (int i = temp - 1; i >= 0; i--)
            {
                dequeue->array[i + 1] = dequeue->array[i];
            } // shifting the array right
        }
        dequeue->array[0] = elem;
        dequeue->n++;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

void pushBack(DequeuePointer dequeue, ElementType elem)
{
    if (dequeue != NULL)
    {
        dequeue->n++;
        dequeue->array[dequeue->n - 1] = elem;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}
DequeuePointer clearDequeue(DequeuePointer dequeue)
{
    for (int i = 0; i < dequeue->n; i++) // initialize the stack to 0
    {
        popBack(dequeue);
    }
    dequeue->n = 0; // size is 0

    return dequeue;
}

ElementType front(DequeuePointer dequeue)
{
    if (dequeue != NULL)
    {
        if (dequeue->n != 0)
        {
            return dequeue->array[0];
        }
        else if (dequeue->n == 0)
        {
            return -1;
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

ElementType back(DequeuePointer dequeue)
{
    if (dequeue != NULL)
    {
        if (dequeue->n != 0)
        {
            return dequeue->array[dequeue->n - 1];
        }
        else if (dequeue->n == 0)
        {
            return -1;
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

int isEmpty(DequeuePointer dequeue)
{
    if (dequeue != NULL)
    {
        if (dequeue->n == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

Size size(DequeuePointer dequeue)
{
    if (dequeue != NULL)
    {
        return dequeue->n;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

int main()
{
    DequeuePointer deque = initDequeue();
    // Do any operation here
    return 0;
}
// Dequeue implementation as an array here,
// Dequeues can also be implemented as linked lists to manage memory more efficiently