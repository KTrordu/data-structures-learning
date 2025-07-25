#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    Node* next;
} Node;

typedef struct list
{
    Node* head;
    int elemcount;
} List;

void init_list(List* list)
{
    list->head = NULL;
    list->elemcount = 0;
}

void add_front(List* list, int new_elem)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_elem;
    new_node->next = list->head;
    
    list->head = new_node;
    list->elemcount++;
}

void remove_front(List* list)
{
    if (list->head != NULL)
    {
        Node* old = list->head;
        list->head = old->next;
        free(old);
        list->elemcount--;
    }
}

int front(List* list)
{
    if(list->elemcount <= 0)
    {
        return -1;
    }
    return list->head->data;
}

int main()
{


    return EXIT_SUCCESS;
}