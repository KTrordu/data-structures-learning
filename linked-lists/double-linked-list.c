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
void add_front(intDoubleList *list, int new_element);
void remove_front(intDoubleList *list);
void add_back(intDoubleList *list, int new_element);
void remove_back(intDoubleList *list);
void add_at_a_position(intDoubleList *list, int new_element, int position);
void remove_at_a_position(intDoubleList *list, int position);
void print_list_head_to_tail(intDoubleList *list);
void print_list_tail_to_head(intDoubleList *list);

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

void add_front(intDoubleList *list, int new_element)
{
    intNode *new_node = (intNode*)malloc(sizeof(intNode*));
    new_node->data = new_element;
    new_node->next = list->head;
    list->head = new_node;
    list->elemCount++;
}

void remove_front(intDoubleList *list)
{
    if(list->head != NULL)
    {
        intNode *old = list->head;
        list->head = list->head->next;
        free(old);
        list->elemCount--;
    }
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

void add_at_a_position(intDoubleList *list, int new_element, int position)
{
    if(position == 0)
    {
        add_front(list, new_element);
        return;
    }
    else if (position > list->elemCount) return;

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
    new_node->previous = prev_node;
    new_node->next = position_ptr;

    if(position_ptr != NULL) position_ptr->previous = new_node;

    if(position == list->elemCount) list->tail = new_node;

    list->elemCount++;
}

void remove_at_a_position(intDoubleList *list, int position)
{
    if(position == 0)
    {
        remove_front(list);
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

    prev_node->next = position_ptr;

    if(position_ptr->next != NULL) position_ptr->next->previous = prev_node;

    if(position == list->elemCount - 1) list->tail = prev_node;

    free(position_ptr);
    list->elemCount--;
}

void print_list_head_to_tail(intDoubleList *list)
{
    for (intNode *ptr = list->head; ptr != NULL; ptr = ptr->next)
    {
        printf("%d\n", ptr->data);
    }
}

void print_list_tail_to_head(intDoubleList *list)
{
    for (intNode *ptr = list->tail; ptr != NULL; ptr = ptr->previous)
    {
        printf("%d\n", ptr->data);
    }
}