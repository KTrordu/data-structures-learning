#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 5

typedef struct intNode
{
    int data;
    struct intNode *next;
    struct intNode *previous;
} intNode;

typedef struct intDoubleList
{
    intNode *head;
    intNode *tail;
    int elemCount;
} intDoubleList;

void init_double_list(intDoubleList  *list);
void add_back(intDoubleList *list, int new_element);
void remove_back(intDoubleList *list);

int main()
{
    

    return EXIT_SUCCESS;
}

void init_list(intDoubleList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->elemCount = 0;
}

void add_back(intDoubleList *list, int new_element)
{
    intNode *new_node = (intNode*)malloc(sizeof(intNode));
    new_node->data = new_element;
    new_node->next = NULL;
    new_node->previous = list->tail;

    if(list->tail != NULL)
    {
        list->tail->next = new_node;
    }

    list->tail = new_node;
    list->elemCount++;

    if (list->elemCount == 1)
    {
        list->head = new_node;
    }
}

void remove_back(intDoubleList *list)
{
    if (list->tail != NULL)
    {
        intNode *old = list->tail;

        if(list->tail->previous != NULL)
        {
            list->tail->next = NULL;
        }

        list->tail = list->tail->previous;
        free(old);
        list->elemCount--;

        if(list->elemCount == 0)
        {
            list->head = NULL;
            list->tail = NULL;
        }
    }
}