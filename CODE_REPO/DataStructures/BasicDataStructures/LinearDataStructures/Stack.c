#include <stdio.h>
#include <stdlib.h>

typedef struct stack Stack;
typedef struct stack *StackPointer;
typedef int ElementType;
typedef long int Size;
struct stack
{
    Size N; // size of stack
    ElementType array[100000];
};

// Initialise the stack
StackPointer initStack()
{
    StackPointer stack = (StackPointer)malloc(sizeof(Stack)); // Allocate memory
    if (stack == NULL)
    {
        exit(EXIT_FAILURE); // exit if fail
    }
    stack->N = 0;                    // size is 0
    for (int i = 0; i < 100000; i++) // initialize the stack to 0
    {
        stack->array[i] = 0;
    }
    return stack;
}

ElementType pop(StackPointer stack)
{
    ElementType ret;
    if (stack != NULL) // if stack exists
    {
        if (stack->N != 0) // if size is not null
        {
            ret = stack->array[0]; // first element is returned
            Size s = 0;
            while (s < stack->N)
            {
                stack->array[s] = stack->array[s + 1];
                s++;
            } // shifting of array towards left

            stack->N--;

            return ret;
        }
        if (stack->N == 0)
        {
            return -1;
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    // return ret;
}

StackPointer clearStack(StackPointer stack)
{

    stack->N = 0;                      // size is 0
    for (int i = 0; i < stack->N; i++) // initialize the stack to 0
    {
        pop(stack);
    }
    return stack;
}

void push(StackPointer stack, ElementType elem)
{
    if (stack != NULL) // if stack exists
    {
        if (stack->N > 0) // if already has elements
        {
            Size temp = stack->N;

            for (int i = temp - 1; i >= 0; i--)
            {

                stack->array[i + 1] = stack->array[i];

            } // push array right
        }
        stack->array[0] = elem; // push element to 0
        stack->N++;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

ElementType top(StackPointer stack)
{
    if (stack != NULL) // if stck exists
    {
        if (stack->N != 0) // if elements are already present
        {
            return stack->array[0];
        }
        else if (stack->N == 0)
        {
            return -1;
        }
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    return (stack->N == 0 ? -1 : stack->array[0]);
}

int isEmpty(StackPointer stack)
{
    if (stack != NULL)
    {
        if (stack->N == 0)
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

Size size(StackPointer stack)
{
    if (stack != NULL)
    {
        return stack->N;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

int main()
{
    StackPointer stack = initStack();
    // Do any operation here
    return 0;
}

// Stack implementation as an array here,
// Stacks can also be implemented as linked lists to manage memory more efficiently