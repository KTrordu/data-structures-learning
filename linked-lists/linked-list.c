#include <stdio.h>
#include <stdlib.h>

typedef struct intNode
{
    int data;
    struct intNode *next;
} intNode;

typedef struct intList
{
    intNode *head;
    int elemCount;
} intList;

int main()
{
    intNode* Node1 = (intNode*)malloc(sizeof(intNode));
    intNode* Node2 = (intNode*)malloc(sizeof(intNode));
    intNode* Node3 = (intNode*)malloc(sizeof(intNode));

    Node1->data = 1;
    Node2->data = 2;
    Node3->data = 3;

    Node1->next = Node2;
    Node2->next = Node3;
    Node3->next = NULL;

    intList list;
    list.head = Node1;
    list.elemCount = 3;

    intNode* ptr = list.head;
    while (ptr != NULL)
    {
        printf("%d\n", ptr->data);
        ptr = ptr->next;
    }

    free(Node1);
    free(Node2);
    free(Node3);

    return EXIT_SUCCESS;
}