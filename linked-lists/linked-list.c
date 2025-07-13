#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 3

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

void init_list(intList *list);
void add_front(intList *list, intNode *new_node);
void remove_front(intList *list);

int main()
{
    intList list;
    init_list(&list);

    for (int i = LIST_SIZE; i > 0; i--)
    {
        intNode *new_node = (intNode*)malloc(sizeof(intNode));
        new_node->data = i;
        add_front(&list, new_node);
    }

    intNode *temp = list.head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    return EXIT_SUCCESS;
}

void init_list(intList *list)
{
    list->head = NULL;
    list->elemCount = 0;
}

void add_front(intList *list, intNode *new_node)
{
    new_node->next = list->head;
    list->head = new_node;
    list->elemCount++;
}

void remove_front(intList *list)
{
    if(list->head != NULL)
    {
        intNode *old = list->head;
        list->head = list->head->next;
        free(old);
        list->elemCount--;
    }
}