#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1
typedef struct Graph GRAPH;
typedef struct Graph *GHPtr;
typedef struct GraphNode GNODE;
typedef struct GraphNode *GNPtr;
typedef struct GraphEdge GEDGE;
typedef struct GraphEdge *GEPtr;
typedef struct LNode LNODE;
typedef struct LNode *LNPtr;
typedef struct List LIST;
typedef struct List *LPtr;
typedef struct Queue QUEUE;
typedef struct Queue *QPtr;

// Although graphs are a general concept using self loops
// and multiple edges between 2 vertices ,
// we just assume that in there is at max one edge between 2 vertices
// in case of undirected graph the edge between 1 to 2 is the same as 2 to 1
// source and destination are meaningless there.
// Only the construction of undirected and directed graphs are different
struct List
{
    LNPtr Head;
    LNPtr Tail;
};

struct Queue
{
    int Num;
    LNPtr Head;
    LNPtr Tail;
};

struct LNode
{
    int val;
    LNPtr Prev;
    LNPtr Next;
};

struct Graph
{
    int V;          // No of vertices
    int E;          // No of edges
    LPtr AdjList;   // AdjacencyList
    GNPtr Vertices; // List of verices
    GEPtr Edges;    // List of Edges
};

struct GraphNode
{
    int Num;   // Number of vertex in added order starts from 1;
    int Value; // Key stored in vertex
};

struct GraphEdge
{
    // In case of directed graphs / undirected graphs could be handled the same
    int Source;
    int Destination;
    int Weight; // Weight of edge
};

LNPtr initNode(int X)
{
    LNPtr Node = (LNPtr)malloc(sizeof(LNODE));
    if (Node == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Node->val = X;
    Node->Next = NULL;
    Node->Prev = NULL;
    return Node;
}

QPtr initQueue()
{
    QPtr Q = (QPtr)malloc(sizeof(QUEUE));
    if (Q == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Q->Num = 0;
    Q->Head = NULL;
    Q->Tail = NULL;
    return Q;
}

void Enqueue(QPtr Q, int Val)
{
    if (Q != NULL)
    {
        if (Q->Tail != NULL)
        {
            LNPtr temp = Q->Tail;
            Q->Tail = initNode(Val);
            Q->Tail->Prev = temp;
            temp->Next = Q->Tail;
        }
        else
        {
            Q->Head = Q->Tail = initNode(Val);
        }
        Q->Num++;
    }
}

int Dequeue(QPtr Q)
{
    if (Q != NULL)
    {
        if (Q->Head != NULL)
        {
            LNPtr temp = Q->Head;
            int ret = Q->Head->val;
            Q->Head = Q->Head->Next;
            if (Q->Head != NULL)
            {
                Q->Head->Prev = NULL;
            }
            else
            {
                Q->Tail = Q->Head;
            }
            free(temp);
            Q->Num--;
            return ret;
        }
    }
}

int isQEmpty(QPtr Q)
{
    if (Q != NULL)
    {
        if (Q->Num == 0)
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
        return -1;
    }
}

void PrintQueue(QPtr Q)
{
    if (Q != NULL)
    {
        if (Q->Head != NULL)
        {
            LNPtr temp = Q->Head;
            while (temp != NULL)
            {
                printf("%d ", temp->val);
                temp = temp->Next;
            }
            printf("\n");
        }
    }
}

GHPtr initdirectedGraph()
{
    GHPtr Graph = (GHPtr)malloc(sizeof(GRAPH));
    Graph->V = 0;
    Graph->E = 0;
    Graph->Vertices = NULL;
    Graph->AdjList = NULL;
    Graph->Edges = NULL;
    return Graph;
}

GHPtr initUndirectedGraph()
{
    GHPtr Graph = (GHPtr)malloc(sizeof(GRAPH));
    Graph->V = 0;
    Graph->E = 0;
    Graph->Vertices = NULL;
    Graph->AdjList = NULL;
    return Graph;
}

// Both function do same thing
// but they are made different for the sake of clarity

// Adding all vertices in all go
void addVerticesToDirectedGraph(GHPtr Graph, int *value, int N)
{

    GNPtr Vertex = (GNPtr)malloc(N * sizeof(GNODE));
    if (Vertex == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= N; i++)
    {
        Vertex[i - 1].Num = i;
        Vertex[i - 1].Value = value[i - 1];
    }
    Graph->Vertices = Vertex;
    Graph->V = N;
}

void addVerticesToUndirectedGraph(GHPtr Graph, int *value, int N)
{

    GNPtr Vertex = (GNPtr)malloc(N * sizeof(GNODE));
    if (Vertex == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= N; i++)
    {
        Vertex[i - 1].Num = i;
        Vertex[i - 1].Value = value[i - 1];
    }
    Graph->Vertices = Vertex;
    Graph->V = N;
}

// Both function do same thing
// but they are made different for the sake of clarity
// It supports multiple edges / self loops for the Directed Graph
void addEdgeToDirectedGraph(GHPtr Graph, int *valueSource, int *valueDest, int *EdgeAttr, int N)
{
    GEPtr Edge = (GEPtr)malloc(N * sizeof(GEDGE));
    if (Edge == NULL)
    {
        exit(EXIT_FAILURE);
    }
    // Init Adjacency List
    Graph->AdjList = (LPtr)malloc((Graph->V) * sizeof(LIST));
    for (int i = 1; i <= Graph->V; i++)
    {
        Graph->AdjList[i - 1].Head = NULL;
        Graph->AdjList[i - 1].Tail = NULL;
    }
    // Add Edge
    for (int i = 1; i <= N; i++)
    {
        // init Node
        LNPtr Node = (LNPtr)malloc(sizeof(LNODE));
        Node->Next = NULL;
        Node->Prev = NULL;
        Node->val = valueDest[i - 1];
        // Add Edge
        Edge[i - 1].Source = valueSource[i - 1];
        Edge[i - 1].Destination = valueDest[i - 1];
        Edge[1 - 1].Weight = EdgeAttr[i - 1];
        // Update Adjacency List
        LNPtr temp = Graph->AdjList[valueSource[i - 1] - 1].Tail;
        Graph->AdjList[valueSource[i - 1] - 1].Tail = Node;
        Node->Next = NULL;
        Node->Prev = temp;
        if (Node->Prev == NULL)
        {
            Graph->AdjList[valueSource[i - 1] - 1].Head = Node;
        }
        else
        {
            temp->Next = Node;
        }
    }
    Graph->Edges = Edge;
    Graph->E = N;
}

// Fun Fact-- This allows self loops/multiple edges in the undirected graph
//  Theoritically self loops are not possible in undirected graphs
void addEdgeToUndirectedGraph(GHPtr Graph, int *valueSource, int *valueDest, int *EdgeAttr, int N)
{
    GEPtr Edge = (GEPtr)malloc(N * sizeof(GEDGE));
    if (Edge == NULL)
    {
        exit(EXIT_FAILURE);
    }
    // Init Adjacency List
    Graph->AdjList = (LPtr)malloc((Graph->V) * sizeof(LIST));
    for (int i = 1; i <= Graph->V; i++)
    {
        Graph->AdjList[i - 1].Head = NULL;
        Graph->AdjList[i - 1].Tail = NULL;
    }
    // Add Edge
    for (int i = 1; i <= N; i++)
    {
        // init Node for source
        LNPtr NodeS = (LNPtr)malloc(sizeof(LNODE));
        NodeS->Next = NULL;
        NodeS->Prev = NULL;
        NodeS->val = valueDest[i - 1];
        // init Node for destination
        LNPtr NodeD = (LNPtr)malloc(sizeof(LNODE));
        NodeD->Next = NULL;
        NodeD->Prev = NULL;
        NodeD->val = valueSource[i - 1];
        // Add Edge
        Edge[i - 1].Source = valueSource[i - 1];
        Edge[i - 1].Destination = valueDest[i - 1];
        Edge[1 - 1].Weight = EdgeAttr[i - 1];
        // Note that Source and Destination have no meaning
        // for an undirected graph
        // Update Adjacency List for Source
        LNPtr tempS = Graph->AdjList[valueSource[i - 1] - 1].Tail;
        Graph->AdjList[valueSource[i - 1] - 1].Tail = NodeS;
        NodeS->Next = NULL;
        NodeS->Prev = tempS;
        if (NodeS->Prev == NULL)
        {
            Graph->AdjList[valueSource[i - 1] - 1].Head = NodeS;
        }
        else
        {
            tempS->Next = NodeS;
        }
        // Update Adjacency List for Destination
        if (valueSource[i - 1] != valueDest[i - 1]) // to handle self loops
        {
            LNPtr tempD = Graph->AdjList[valueDest[i - 1] - 1].Tail;
            Graph->AdjList[valueDest[i - 1] - 1].Tail = NodeD;
            NodeD->Next = NULL;
            NodeD->Prev = tempD;
            if (NodeD->Prev == NULL)
            {
                Graph->AdjList[valueDest[i - 1] - 1].Head = NodeD;
            }
            else
            {
                tempD->Next = NodeD;
            }
        }
    }
    Graph->Edges = Edge;
    Graph->E = N;
}

GHPtr createDirGraph(int V, int E, int *EdgeAttr, int *Vertex, int *ESource, int *EDest)
{
    GHPtr Graph = initdirectedGraph();
    addVerticesToDirectedGraph(Graph, Vertex, V);
    addEdgeToDirectedGraph(Graph, ESource, EDest, EdgeAttr, E);
    return Graph;
}

GHPtr createUndirGraph(int V, int E, int *EdgeAttr, int *Vertex, int *ESource, int *EDest)
{
    GHPtr Graph = initUndirectedGraph();
    addVerticesToUndirectedGraph(Graph, Vertex, V);
    addEdgeToUndirectedGraph(Graph, ESource, EDest, EdgeAttr, E);
    return Graph;
}

void printGraph(GHPtr Graph)
{
    for (int i = 1; i <= Graph->V; i++)
    {
        printf("%d(%d):", Graph->Vertices[i - 1].Num, Graph->Vertices[i - 1].Value);
        LNPtr temp = Graph->AdjList[i - 1].Head;
        while (temp != NULL)
        {
            printf("%d ", temp->val);
            temp = temp->Next;
        }
        printf("\n");
    }
}

void scanArray(int *A, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

void scanEdge(int *A, int *B, int E)
{
    for (int i = 0; i < E; i++)
    {
        scanf("%d", &A[i]);
        scanf("%d", &B[i]);
    }
}

// Works on multiple edges and self loops
int **BFS(GHPtr Graph, int Source)
{
    int **BFSis = (int **)malloc(5 * sizeof(int *));
    for (int i = 1; i <= 5; i++)
    {
        BFSis[i - 1] = (int *)malloc((Graph->V) * sizeof(int));
    }
    for (int i = 1; i <= Graph->V; i++)
    {
        if (i != Source)
        {
            BFSis[0][i - 1] = WHITE;
            BFSis[1][i - 1] = INT_MAX;
            BFSis[2][i - 1] = NIL;
        }
    }
    int Visited = 0;
    BFSis[0][Source - 1] = GRAY;
    BFSis[1][Source - 1] = 0;
    BFSis[2][Source - 1] = NIL;
    Visited = Visited + 1;
    BFSis[3][Visited - 1] = Source;
    BFSis[4][Visited - 1] = Graph->Vertices[Source - 1].Value;
    QPtr Q = initQueue();
    Enqueue(Q, Source);
    while (!isQEmpty(Q))
    {
        int U = Dequeue(Q);
        LNPtr temp = Graph->AdjList[U - 1].Head;
        while (temp != NULL)
        {
            if (BFSis[0][temp->val - 1] == WHITE)
            {
                BFSis[0][temp->val - 1] = GRAY;
                BFSis[1][temp->val - 1] = BFSis[1][U - 1] + 1;
                BFSis[2][temp->val - 1] = U;
                Visited = Visited + 1;
                BFSis[3][Visited - 1] = temp->val;
                BFSis[4][Visited - 1] = Graph->Vertices[temp->val - 1].Value;
                Enqueue(Q, temp->val);
            }

            temp = temp->Next;
        }
        BFSis[0][U - 1] = BLACK;
    }
    return BFSis;
}
// Note that many BFS are possible in a given graph
// even if the source is same , the order of the visited vertices
// may be different. It depends on the edges on the adjacency List.

void printPath(GHPtr Graph, int **BFS, int Source, int Dest)
{
    if (Source > Graph->V || Dest > Graph->V)
    {
        return;
    }
    else if (Source == Dest)
    {
        printf("%d(%d)", Graph->Vertices[Source - 1].Num, Graph->Vertices[Source - 1].Value);
    }
    else if (BFS[2][Dest - 1] == NIL)
    {
        printf("NO PATH EXISTS BETWEEN (%d) AND (%d)", Graph->Vertices[Source - 1].Num, Graph->Vertices[Dest - 1].Num);
    }
    else
    {
        printPath(Graph, BFS, Source, BFS[2][Dest - 1]);
        printf("->%d(%d)", Graph->Vertices[Dest - 1].Num, Graph->Vertices[Dest - 1].Value);
    }
}
// Prints the Shortest path from the source to any given vertex V, given the BFS
// from the Source.

int DFSvisit(GHPtr Graph, int time, int **DFS, int Vertex, int *Visited)
{
    time = time + 1;
    DFS[3][Vertex - 1] = time;
    (*Visited)++;
    DFS[2][(*Visited) - 1] = Vertex;
    DFS[0][Vertex - 1] = GRAY;
    LNPtr temp = Graph->AdjList[Vertex - 1].Head;
    while (temp != NULL)
    {
        if (DFS[0][temp->val - 1] == WHITE)
        {
            DFS[1][temp->val - 1] = Vertex;
            time = DFSvisit(Graph, time, DFS, temp->val, Visited);
        }
        temp = temp->Next;
    }
    DFS[0][Vertex - 1] = BLACK;
    time = time + 1;
    DFS[4][Vertex - 1] = time;
    return time;
}

int **DFS(GHPtr Graph)
{
    int *Visited = (int *)malloc(sizeof(int));
    int **DFSis = (int **)malloc(5 * sizeof(int *));
    for (int i = 1; i <= 5; i++)
    {
        DFSis[i - 1] = (int *)malloc((Graph->V) * sizeof(int));
    }
    for (int i = 1; i <= Graph->V; i++)
    {
        DFSis[0][i - 1] = WHITE;
        DFSis[1][i - 1] = NIL;
    }
    int time = 0;
    for (int i = 1; i <= Graph->V; i++)
    {
        if (DFSis[0][i - 1] == WHITE)
        {
            time = DFSvisit(Graph, time, DFSis, i, Visited);
        }
    }
    return DFSis;
}
// Many DFS are possible for a graph, with many diferent DFS tree's,
// This depends on the Nodes and they way they are attached in the adjaceny list.u

// Modified DFS for topological Sort
int DFSvisitMod(GHPtr Graph, int time, int **DFS, int Vertex, int *Visited, int *Finished)
{
    time = time + 1;
    DFS[3][Vertex - 1] = time;
    (*Visited)++;
    DFS[2][(*Visited) - 1] = Vertex;
    DFS[0][Vertex - 1] = GRAY;
    LNPtr temp = Graph->AdjList[Vertex - 1].Head;
    while (temp != NULL)
    {
        if (DFS[0][temp->val - 1] == WHITE)
        {
            DFS[1][temp->val - 1] = Vertex;
            time = DFSvisitMod(Graph, time, DFS, temp->val, Visited, Finished);
        }
        temp = temp->Next;
    }
    DFS[0][Vertex - 1] = BLACK;
    time = time + 1;
    DFS[4][Vertex - 1] = time;
    (*Finished)++;
    DFS[5][(*Finished) - 1] = Vertex;
    return time;
}

int **DFSmod(GHPtr Graph)
{
    int *Visited = (int *)malloc(sizeof(int));
    int *Finished = (int *)malloc(sizeof(int));
    int **DFSis = (int **)malloc(6 * sizeof(int *));
    for (int i = 1; i <= 6; i++)
    {
        DFSis[i - 1] = (int *)malloc((Graph->V) * sizeof(int));
    }
    for (int i = 1; i <= Graph->V; i++)
    {
        DFSis[0][i - 1] = WHITE;
        DFSis[1][i - 1] = NIL;
    }
    int time = 0;
    for (int i = 1; i <= Graph->V; i++)
    {
        if (DFSis[0][i - 1] == WHITE)
        {
            time = DFSvisitMod(Graph, time, DFSis, i, Visited, Finished);
        }
    }
    return DFSis;
}

// Only for directed acyclic graphs
int *TopologicalSort(GHPtr Graph)
{
    int **Dfs = DFSmod(Graph);
    int *Ret = (int *)malloc((Graph->V) * sizeof(int));
    for (int i = 1; i <= Graph->V; i++)
    {
        Ret[i - 1] = Dfs[5][i - 1];
    }
    return Ret;
}
// It sorts the vertices from right to left , 
// i.e. edges flow from right to left only.
// To get a reverse sorting(left to right) , just reverse Ret array.



int main()
{
    int V;
    printf("Enter the number of vertices in the Graph:");
    scanf("%d", &V); // Enter the vertices here
    int E;
    printf("Enter the number of edges in the Graph:");
    scanf("%d", &E); // Enter the Edges here
    int Ver[V];
    printf("Enter the value of the vertex:\n");
    scanArray(Ver, V);
    int valS[E];
    int valD[E];
    printf("Enter the Edges:\n");
    scanEdge(valS, valD, E);
    int EAttr[E];
    printf("Enter the Edge Attribute:\n");
    scanArray(EAttr, E);
    // GHPtr GraphU = createUndirGraph(V, E, EAttr, Ver, valS, valD);
    GHPtr GraphD = createDirGraph(V, E, EAttr, Ver, valS, valD);
    printf("Directed Graph:\n");
    printGraph(GraphD);
    // printf("Undirected Graph:\n");
    // printGraph(GraphU);
    // Do any operartions here
    return 0;
}
// Please give proper input for proper working