#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryTree TREE;
typedef struct BinaryTree *TreePointer;
typedef struct Node TreeNode;
typedef struct Node *NodePointer;
typedef long long int LONG;
struct Node
{
    LONG value;             // Value of node
    NodePointer parent;     // parent Node
    NodePointer leftChild;  // left child
    NodePointer rightChild; // right child
};

struct BinaryTree
{
    NodePointer Root;
};

TreePointer CreateBinaryTree()
{
    TreePointer Tree = (TreePointer)malloc(sizeof(TREE));
    if (Tree == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Tree->Root = NULL;
    return Tree;
}

void InorderWalk(NodePointer Node)
{
    if (Node != NULL)
    {
        InorderWalk(Node->leftChild);
        printf("%lld ", Node->value);
        InorderWalk(Node->rightChild);
    }
}

void PreorderWalk(NodePointer Node)
{
    if (Node != NULL)
    {
        printf("%lld ", Node->value);
        PreorderWalk(Node->leftChild);
        PreorderWalk(Node->rightChild);
    }
}

void PostorderWalk(NodePointer Node)
{
    if (Node != NULL)
    {
        PostorderWalk(Node->leftChild);
        PostorderWalk(Node->rightChild);
        printf("%lld ", Node->value);
    }
}

NodePointer TreeSearchBST(NodePointer Node, LONG key)
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

NodePointer IterativeTreeSearchBST(NodePointer Node, LONG key)
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

NodePointer TreeMinimumBST(NodePointer Node)
{
    while (Node->leftChild != NULL)
    {
        Node = Node->leftChild;
    }
    return Node;
}

NodePointer TreeMaximumBST(NodePointer Node)
{
    while (Node->rightChild != NULL)
    {
        Node = Node->rightChild;
    }
    return Node;
}

NodePointer TreeSuccessorBST(NodePointer Node)
{
    if (Node->rightChild != NULL)
    {
        return TreeMinimumBST(Node->rightChild);
    }
    NodePointer y = Node->parent;
    while ((y != NULL) && (Node = y->rightChild))
    {
        Node = y;
        y = y->parent;
    }
    return y;
}

NodePointer TreePredecessorBST(NodePointer Node)
{
    if (Node->leftChild != NULL)
    {
        return TreeMaximumBST(Node->leftChild);
    }
    NodePointer y = Node->parent;
    while ((y != NULL) && (Node = y->leftChild))
    {
        Node = y;
        y = y->parent;
    }
    return y;
}

void InsertNodeBST(TreePointer Tree, LONG key)
{
    NodePointer Node = (NodePointer)malloc(sizeof(TreeNode));
    Node->value = key;
    Node->leftChild = NULL;
    Node->rightChild = NULL;
    Node->parent = NULL;
    NodePointer y = NULL;
    NodePointer x = Tree->Root;
    while (x != NULL)
    {
        y = x;
        if (Node->value < x->value)
        {
            x = x->leftChild;
        }
        else
        {
            x = x->rightChild;
        }
    }
    Node->parent = y;
    if (y == NULL)
    {
        Tree->Root = Node;
    }
    else if (Node->value < y->value)
    {
        y->leftChild = Node;
    }
    else
    {
        y->rightChild = Node;
    }
}

void Transplant(TreePointer Tree, NodePointer U, NodePointer V)
{
    if (U->parent == NULL)
    {
        Tree->Root = V;
    }
    else if (U == U->parent->leftChild)
    {
        U->parent->leftChild = V;
    }
    else
    {
        U->parent->rightChild = V;
    }
    if (V != NULL)
    {
        V->parent = U->parent;
    }
}

void DeleteNodeBST(TreePointer Tree, LONG key)
{
    NodePointer Node = TreeSearchBST(Tree->Root, key);
    if (Node->leftChild == NULL)
    {
        Transplant(Tree, Node, Node->rightChild);
    }
    else if (Node->rightChild == NULL)
    {
        Transplant(Tree, Node, Node->leftChild);
    }
    else
    {
        NodePointer y = TreeMinimumBST(Node->rightChild);
        if (y->parent != Node)
        {
            Transplant(Tree, y, y->rightChild);
            y->rightChild = Node->rightChild;
            y->rightChild->parent = y;
        }
        Transplant(Tree, Node, y);
        y->leftChild = Node->leftChild;
        y->leftChild->parent = y;
    }
    free(Node);
}

void DeleteTree(NodePointer Node)
{
    if (Node != NULL)
    {
        DeleteTree(Node->leftChild);
        DeleteTree(Node->rightChild);
        free(Node);
    }
}

int main()
{
    TreePointer tree = CreateBinaryTree();
    //Do any operation here
    return 0;
}