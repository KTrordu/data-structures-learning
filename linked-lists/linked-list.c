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
void add(intList *list, intNode *new_node, int position);
void remove_at_position(intList *list, int position);

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

    intNode *add_node = (intNode*)malloc(sizeof(intNode));
    add_node->data = 99;
    add(&list, add_node, 1);

    remove_at_position(&list, 0);

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

void add(intList *list, intNode *new_node, int position)
{
    if(position == 0)
    {
        add_front(list, new_node);
        return;
    }
    else if(position > list->elemCount) return;

    intNode *prev_node = NULL;
    intNode *position_ptr = list->head;

    for (int index = 0; index < position; index++)
    {
        prev_node = position_ptr;
        position_ptr = position_ptr->next;
    }

    prev_node->next = new_node;
    new_node->next = position_ptr;
    list->elemCount++;
}

void remove_at_position(intList *list, int position)
{
    if(position == 0)
    {
        remove_front(list);
        return;
    }
    else if(position >= list->elemCount) return;

    intNode *prev_node = NULL;
    intNode *position_ptr = list->head;

    for (int index = 0; index < position; index++)
    {
        prev_node = position_ptr;
        position_ptr = position_ptr->next;
    }

    intNode *old = position_ptr;
    prev_node->next = position_ptr->next;
    free(old);
    list->elemCount--;
}