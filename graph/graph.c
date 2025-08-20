#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int id;
    struct Node** adj;
    int capacity;
    int numAdj;
} Node;

typedef struct Graph
{
    Node** nodes;
    int numNodes;
    int capacity;
} Graph;

Graph* createGraph()
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->nodes = NULL;
    graph->numNodes = 0;
    graph->capacity = 0;
    return graph;
}

Node* createNode(int id)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->adj = NULL;
    newNode->capacity = 0;
    newNode->numAdj = 0;
    return newNode;
}

void addEdgeToNode(Node* node, Node* adjacentNode)
{
    if(node->capacity == node->numAdj)
    {
        int newCapacity = node->capacity == 0 ? 2 : node->capacity * 2;
        Node** newAdj = (Node**)malloc(newCapacity * sizeof(Node*));

        for(int i = 0; i < node->numAdj; i++)
        {
            newAdj[i] = node->adj[i];
        }

        free(node->adj);
        node->adj = newAdj;
        node->capacity = newCapacity;
    }
    node->adj[node->numAdj++] = adjacentNode;
}

void addNodeToGraph(Graph* graph, int id)
{
    if(graph->capacity == graph->numNodes)
    {
        int newCapacity = graph->capacity == 0 ? 4 : graph->capacity * 2;
        Node** newNodes = (Node**)malloc(newCapacity * sizeof(Node*));

        for(int i = 0; i < graph->numNodes; i++)
        {
            newNodes[i] = graph->nodes[i];
        }

        free(graph->nodes);
        graph->nodes = newNodes;
        graph->capacity = newCapacity;
    }

    graph->nodes[graph->numNodes++] = createNode(id);
}

void addEdgeToGraph(Graph* graph, int u, int v)
{
    if(u < graph->numNodes && v < graph->numNodes && u != v)
    {
        addEdgeToNode(graph->nodes[u], graph->nodes[v]);
    }
}

void printGraph(Graph* graph)
{
    for(int i = 0; i < graph->numNodes; i++)
    {
        printf("Node %d has edges to: ", graph->nodes[i]->id);
        for(int j = 0; j < graph->nodes[i]->numAdj; j++)
        {
            printf("%d ", graph->nodes[i]->adj[j]->id);
        }
        printf("\n");
    }
}

void freeNode(Node* node)
{
    if(node->adj != NULL)
    {
        free(node->adj);
    }
    free(node);
}

void freeGraph(Graph* graph)
{
    for(int i = 0; i < graph->numNodes; i++)
    {
        freeNode(graph->nodes[i]);
    }
    free(graph->nodes);
    free(graph);
}

int main()
{
    Graph* g = createGraph();

    addNodeToGraph(g, 0);
    addNodeToGraph(g, 1);
    addNodeToGraph(g, 2);
    addNodeToGraph(g, 3);

    addEdgeToGraph(g, 0, 1);
    addEdgeToGraph(g, 0, 2);
    addEdgeToGraph(g, 1, 2);
    addEdgeToGraph(g, 2, 3);
    addEdgeToGraph(g, 3, 0);

    printGraph(g);
    freeGraph(g);

    return EXIT_SUCCESS;
}