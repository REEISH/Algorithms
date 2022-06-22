#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RED 1
#define BLACK 0

typedef struct RBTree RBTREE;
typedef struct RBTree *RBTreePointer;
typedef struct Node RBTreeNode;

typedef struct Node *RBNodePointer;
typedef long long int LONG;
struct Node
{
    int colour;               // RED or BLACK
    LONG value;               // Value of node
    RBNodePointer parent;     // parent Node
    RBNodePointer leftChild;  // left child
    RBNodePointer rightChild; // right child
};

struct RBTree
{
    RBNodePointer Root;
    RBNodePointer SENTINAL; // points to T.nil
};

RBTreePointer CreateRBTree()
{
    RBTreePointer RBTree = (RBTreePointer)malloc(sizeof(RBTREE));
    if (RBTree == NULL)
    {
        exit(EXIT_FAILURE);
    }
    RBTree->SENTINAL = (RBNodePointer)malloc(sizeof(RBTreeNode));
    RBTree->SENTINAL->colour = BLACK;
    RBTree->SENTINAL->value = -1;
    RBTree->SENTINAL->leftChild = NULL;
    RBTree->SENTINAL->rightChild = NULL;
    RBTree->SENTINAL->parent = NULL;
    RBTree->Root = RBTree->SENTINAL;
    return RBTree;
}

// Operations of BST on a Red-Black Tree
void InorderWalk(RBTreePointer RBTree, RBNodePointer Node)
{
    if (Node != RBTree->SENTINAL)
    {
        InorderWalk(RBTree, Node->leftChild);
        printf("%lld ", Node->value);
        InorderWalk(RBTree, Node->rightChild);
    }
}

void PreorderWalk(RBTreePointer RBTree, RBNodePointer Node)
{
    if (Node != RBTree->SENTINAL)
    {
        printf("%lld ", Node->value);
        PreorderWalk(RBTree, Node->leftChild);
        PreorderWalk(RBTree, Node->rightChild);
    }
}

void PostorderWalk(RBTreePointer RBTree, RBNodePointer Node)
{
    if (Node != RBTree->SENTINAL)
    {
        PostorderWalk(RBTree, Node->leftChild);
        PostorderWalk(RBTree, Node->rightChild);
        printf("%lld ", Node->value);
    }
}

RBNodePointer TreeSearchBST(RBNodePointer Node, LONG key)
{
    if ((Node == NULL) || (key = Node->value))
    {
        return Node;
    }

    else if (key < Node->value)
    {
        return TreeSearchBST(Node->leftChild, key);
    }
    else
    {
        return TreeSearchBST(Node->rightChild, key);
    }
}

RBNodePointer IterativeTreeSearchBST(RBNodePointer Node, LONG key)
{
    while ((Node != NULL) && (key != Node->value))
    {
        if (key < Node->value)
        {
            Node = Node->leftChild;
        }
        else
        {
            Node = Node->rightChild;
        }
    }
    return Node;
}

RBNodePointer TreeMinimumBST(RBNodePointer Node)
{
    while (Node->leftChild != NULL)
    {
        Node = Node->leftChild;
    }
    return Node;
}

RBNodePointer TreeMaximumBST(RBNodePointer Node)
{
    while (Node->rightChild != NULL)
    {
        Node = Node->rightChild;
    }
    return Node;
}

RBNodePointer TreeSuccessorBST(RBNodePointer Node)
{
    if (Node->rightChild != NULL)
    {
        return TreeMinimumBST(Node->rightChild);
    }
    RBNodePointer y = Node->parent;
    while ((y != NULL) && (Node = y->rightChild))
    {
        Node = y;
        y = y->parent;
    }
    return y;
}

RBNodePointer TreePredecessorBST(RBNodePointer Node)
{
    if (Node->leftChild != NULL)
    {
        return TreeMaximumBST(Node->leftChild);
    }
    RBNodePointer y = Node->parent;
    while ((y != NULL) && (Node = y->leftChild))
    {
        Node = y;
        y = y->parent;
    }
    return y;
}
// Basic operation on RB tree

void LeftRotate(RBTreePointer T, RBNodePointer X)
{
    RBNodePointer Y = X->rightChild;
    X->rightChild = Y->leftChild;
    if (Y->leftChild != T->SENTINAL)
    {
        Y->leftChild->parent = X;
    }
    Y->parent = X->parent;
    if (X->parent == T->SENTINAL)
    {
        T->Root = Y;
    }
    else if (X == X->parent->leftChild)
    {
        X->parent->leftChild = Y;
    }
    else
    {
        X->parent->rightChild = Y;
    }
    Y->leftChild = X;
    X->parent = Y;
}

void RightRotate(RBTreePointer T, RBNodePointer Y)
{
    RBNodePointer X = Y->leftChild;
    Y->leftChild = X->rightChild;
    if (X->rightChild != T->SENTINAL)
    {
        X->rightChild->parent = Y;
    }
    X->parent = Y->parent;
    if (Y->parent == T->SENTINAL)
    {
        T->Root = X;
    }
    else if (Y == Y->parent->rightChild)
    {
        Y->parent->rightChild = X;
    }
    else
    {
        Y->parent->leftChild = X;
    }
    X->rightChild = Y;
    Y->parent = X;
}

// Insertion in a red-black tree

void RBinsertFixup(RBTreePointer T, RBNodePointer Z)
{
    RBNodePointer Y;
    while (Z->parent->colour == RED)
    {
        if (Z->parent == Z->parent->parent->leftChild)
        {
            Y = Z->parent->parent->rightChild;
            if (Y->colour == RED)
            {
                Z->parent->colour = BLACK;
                Y->colour = BLACK;
                Z->parent->parent->colour = RED;
                Z = Z->parent->parent;
            }
            else
            {
                if (Z == Z->parent->rightChild)
                {
                    Z = Z->parent;
                    LeftRotate(T, Z);
                }
                Z->parent->colour = BLACK;
                Z->parent->parent->colour = RED;
                RightRotate(T, Z->parent->parent);
            }
        }
        else
        {
            if (Z->parent == Z->parent->parent->rightChild)
            {
                Y = Z->parent->parent->leftChild;
                if (Y->colour == RED)
                {
                    Z->parent->colour = BLACK;
                    Y->colour = BLACK;
                    Z->parent->parent->colour = RED;
                    Z = Z->parent->parent;
                }
                else
                {
                    if (Z == Z->parent->leftChild)
                    {
                        Z = Z->parent;
                        RightRotate(T, Z);
                    }
                    Z->parent->colour = BLACK;
                    Z->parent->parent->colour = RED;
                    LeftRotate(T, Z->parent->parent);
                }
            }
        }
    }
    T->Root->colour = BLACK;
}

void RBinsert(RBTreePointer T, LONG key)
{
    RBNodePointer Z = (RBNodePointer)malloc(sizeof(RBTreeNode));
    Z->value = key;
    Z->leftChild = NULL;
    Z->rightChild = NULL;
    Z->parent = NULL;
    RBNodePointer Y = T->SENTINAL;
    RBNodePointer X = T->Root;
    while (X != T->SENTINAL)
    {
        Y = X;
        if (Z->value < X->value)
        {
            X = X->leftChild;
        }
        else
        {
            X = X->rightChild;
        }
    }
    Z->parent = Y;
    if (Y == T->SENTINAL)
    {
        T->Root = Z;
    }
    else if (Z->value < Y->value)
    {
        Y->leftChild = Z;
    }
    else
    {
        Y->rightChild = Z;
    }
    Z->leftChild = T->SENTINAL;
    Z->rightChild = T->SENTINAL;
    Z->colour = RED;
    RBinsertFixup(T, Z);
}

// Deletion from an RB tree

void RBTransplant(RBTreePointer T, RBNodePointer U, RBNodePointer V)
{
    if (U->parent == T->SENTINAL)
    {
        T->Root = V;
    }
    else if (U == U->parent->leftChild)
    {
        U->parent->leftChild = V;
    }
    else
    {
        U->parent->rightChild = V;
    }
    V->parent = U->parent;
}

void RBdeleteFixup(RBTreePointer T, RBNodePointer X)
{
    RBNodePointer W;
    while (X != T->Root && X->colour == BLACK)
    {
        if (X == X->parent->leftChild)
        {
            W = X->parent->rightChild;
            if (W->colour == RED)
            {
                W->colour = BLACK;
                X->parent->colour = RED;
                LeftRotate(T, X->parent);
                W = X->parent->rightChild;
            }
            if (W->leftChild->colour == BLACK && W->rightChild->colour == BLACK)
            {
                W->colour = RED;
                X = X->parent;
            }
            else
            {
                if (W->rightChild->colour == BLACK)
                {
                    W->leftChild->colour = BLACK;
                    W->colour = RED;
                    RightRotate(T, W);
                    W = X->parent->rightChild;
                }
                W->colour = X->parent->colour;
                X->parent->colour = BLACK;
                LeftRotate(T, X->parent);
                X = T->Root;
            }
        }
        else
        {
            if (X == X->parent->rightChild)
            {
                W = X->parent->leftChild;
                if (W->colour == RED)
                {
                    W->colour = BLACK;
                    X->parent->colour = RED;
                    LeftRotate(T, X->parent);
                    W = X->parent->leftChild;
                }
                if (W->rightChild->colour == BLACK && W->leftChild->colour == BLACK)
                {
                    W->colour = RED;
                    X = X->parent;
                }
                else
                {
                    if (W->leftChild->colour == BLACK)
                    {
                        W->rightChild->colour = BLACK;
                        W->colour = RED;
                        LeftRotate(T, W);
                        W = X->parent->leftChild;
                    }
                    W->colour = X->parent->colour;
                    X->parent->colour = BLACK;
                    RightRotate(T, X->parent);
                    X = T->Root;
                }
            }
        }
    }
    X->colour = BLACK;
}

void RBdelete(RBTreePointer T, RBNodePointer Z)
{
    RBNodePointer Y = Z;
    RBNodePointer X;
    int INIT = Y->colour; // Original color is stored
    if (Z->leftChild == T->SENTINAL)
    {
        X = Z->rightChild;
        RBTransplant(T, Z, Z->rightChild);
    }
    else if (Z->rightChild == T->SENTINAL)
    {
        X = Z->leftChild;
        RBTransplant(T, Z, Z->leftChild);
    }
    else
    {
        Y = TreeMinimumBST(Z->rightChild);
        INIT = Y->colour;
        X = Y->rightChild;
        if (Y->parent == Z)
        {
            X->parent = Z;
        }
        else
        {
            RBTransplant(T, Y, Y->rightChild);
            Y->rightChild = Z->rightChild;
            Y->rightChild->parent = Y;
        }
        RBTransplant(T, Z, Y);
        Y->leftChild = Z->leftChild;
        Y->leftChild->parent = Y;
        Y->colour = Z->colour;
    }
    if (INIT == BLACK)
    {
        RBdeleteFixup(T, X);
    }
}

int main()
{
    RBTreePointer RBTree = CreateRBTree();
    // Do any operation here
    return 0;
}