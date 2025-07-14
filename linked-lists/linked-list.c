#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 5

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
void add_front(intList *list, int new_element);
void remove_front(intList *list);
void add(intList *list, int new_element, int position);
void remove_at_position(intList *list, int position);
int get(intList *list, int position);
int length(intList *list);

int main()
{
    intList list;
    init_list(&list);

    for (int i = LIST_SIZE; i > 0; i--)
    {
        add_front(&list, i);
    }

    add(&list, 99, 1);

    remove_at_position(&list, 0);

    for (int i = 0; i < length(&list); i++)
    {
        printf("%d\n", get(&list, i));
    }
    

    return EXIT_SUCCESS;
}

void init_list(intList *list)
{
    list->head = NULL;
    list->elemCount = 0;
}

void add_front(intList *list, int new_element)
{
    intNode *new_node = (intNode*)malloc(sizeof(intNode*));
    new_node->data = new_element;
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

void add(intList *list, int new_element, int position)
{
    if(position == 0)
    {
        add_front(list, new_element);
        return;
    }
    else if(position > list->elemCount) return;

    intNode *new_node = (intNode*)malloc(sizeof(intNode));
    new_node->data = new_element;

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

int get(intList *list, int position)
{
    if(position < 0 || position > list->elemCount)
    {
        printf("Invalid position\n");
        return -1;
    }

    intNode *position_ptr = list->head;
    for (int i = 0; i < position; i++)
    {
        position_ptr = position_ptr->next;
    }
    return position_ptr->data;
}

int length(intList *list)
{
    return list->elemCount;
}