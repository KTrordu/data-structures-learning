#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    Node* next;
} Node;

typedef struct list
{
    Node* cursor;
    int elemcount;
} List;

void init_list(List* list)
{
    list->cursor = NULL;
    list->elemcount = 0;
}

void add_end(List* list, int new_elem)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_elem;

    if(list->cursor == NULL)
    {
        new_node->next = new_node;
        list->cursor = new_node;
    }
    else
    {
        new_node->next = list->cursor->next;
        list->cursor->next = new_node;
        list->cursor = new_node;
    }

    list->elemcount++;
}

void remove_front(List* list)
{
    if(list->cursor == NULL) return;

    Node* to_delete = list->cursor->next;

    if(to_delete == list->cursor)
    {
        list->cursor = NULL;
    }
    else
    {
        list->cursor->next = to_delete->next;
    }

    free(to_delete);
    list->elemcount--;
}

int back(List* list)
{
    if(list->cursor != NULL)
    {
        return list->cursor->data;
    }
    return -1;
}

int front(List* list)
{
    if(list->cursor != NULL)
    {
        return list->cursor->next->data;
    }
    return -1;
}

void advance(List* list)
{
    if (list->cursor != NULL)
    {
        list->cursor = list->cursor->next;
    }
}

int main()
{


    return EXIT_SUCCESS;
}