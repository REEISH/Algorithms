#include <stdio.h>
#include <stdlib.h>

typedef struct queue Queue;
typedef struct queue *QueuePointer;
typedef int ElementType;
typedef long int Size;
struct queue
{
    long int N; // size of queue
    ElementType array[100000];
};

// Initialise the queue
QueuePointer initQueue()
{
    QueuePointer queue = (QueuePointer)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        exit(EXIT_FAILURE);
    }
    queue->N = 0;
    for (int i = 0; i < 100000; i++)
    {
        queue->array[i] = 0;
    }
}

ElementType dequeue(QueuePointer queue)
{
    if (queue != NULL)// queue is not null
    {
        if (queue->N != 0)
        {
            ElementType ret = queue->array[0];
            Size s = 0;
            while (s < queue->N)
            {
                queue->array[s] = queue->array[s + 1];
                s++;
            }
           // queue->array[queue->n - 1] = 0;
            queue->N--;
            return ret;
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

void enqueue(QueuePointer queue, ElementType elem)
{
    if (queue != NULL)
    {
        queue->N++;
        queue->array[queue->N - 1] = elem;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

ElementType front(QueuePointer queue)
{
    if (queue != NULL)
    {
        if (queue->N != 0)
        {
            return queue->array[0];
        }
        else if(queue->N==0)
        {
            return -1;
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

int isEmpty(QueuePointer queue)
{
    if (queue != NULL)
    {
        if (queue->N == 0)
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

Size size(QueuePointer queue)
{
    if (queue != NULL)
    {
        return queue->N;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

int main()
{
    QueuePointer queue = initQueue();
    // Do any operation here
    return 0;
}
// Queue implementation as an array here,
// Queues can also be implemented as linked lists to manage memory more efficiently