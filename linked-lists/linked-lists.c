#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 5

typedef struct Node
{
    int value;
    struct Node *connected_to;
} Node;

int main()
{
    Node *node_list = malloc(sizeof(Node) * 5);

    for (int i = 0; i < 5; i++)
    {
        node_list[i].value = i;
        node_list[i].connected_to = (i == 4) ? &node_list[0] : &node_list[i + 1];
    }

    printf("Nodes' values and connection values:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Node %d: Value = %d, Connection Value = %d\n", i + 1, node_list[i].value, node_list[i].connected_to->value);
    }

    free(node_list);
    return EXIT_SUCCESS;
}