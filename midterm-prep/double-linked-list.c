#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    Node* next;
    Node* prev;
} Node;

typedef struct list
{
    Node* head;
    Node* tail;
    int elemcount;
} List;

void init_list(List* list)
{
    list->head = NULL;
    list->tail = NULL;
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

void add_back(List* list, int new_elem)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_elem;
    new_node->next = NULL;
    new_node->prev = list->tail;

    if(list->head != NULL)
    {
        list->tail->next = new_node;
    }

    list->tail = new_node;
    list->elemcount++;

    if(list->elemcount == 1)
    {
        list->head = new_node;
    }
}

void add_at_pos(List* list, int new_elem, int pos)
{
    if(pos == 0)
    {
        add_front(list, new_elem);
        return;
    }
    else if (pos > list->elemcount) return;

    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_elem;

    Node* prev_node = NULL;
    Node* pos_ptr = list->head;

    for (int i = 0; i < pos; i++)
    {
        prev_node = pos_ptr;
        pos_ptr = pos_ptr->next;
    }

    prev_node->next = new_node;
    new_node->prev = prev_node;
    new_node->next = pos_ptr;

    if(pos_ptr != NULL)
    {
        pos_ptr->prev = new_node;
    }

    if (pos == list->elemcount)
    {
        list->tail = new_node;
    }
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

void remove_back(List* list)
{
    if (list->tail != NULL)
    {
        Node* old = list->tail;

        if(list->tail->prev != NULL)
        {
            list->tail->prev->next = NULL;
        }

        list->tail = old->prev;
        free(old);
        list->elemcount--;

        if(list->elemcount == 0)
        {
            list->head = NULL;
            list->tail = NULL;
        }
    }
}

void remove_at_pos(List* list, int pos)
{
    if(pos == 0)
    {
        remove_front(list);
        return;
    }
    else if (pos >= list->elemcount) return;

    Node* prev_node = NULL;
    Node* pos_ptr = list->head;

    for (int i = 0; i < pos; i++)
    {
        prev_node = pos_ptr;
        pos_ptr = pos_ptr->next;
    }

    prev_node->next = pos_ptr->next;

    if(pos_ptr != NULL)
    {
        pos_ptr->prev = prev_node;
    }

    if(pos == list->elemcount - 1)
    {
        list->tail = prev_node;
    }

    free(pos_ptr);
    list->elemcount--;
}

int front(List* list)
{
    if(list->elemcount <= 0)
    {
        return -1;
    }
    return list->head->data;
}

void print_list_head_to_tail(List* list)
{
    for (Node* pos_ptr = list->head; pos_ptr != NULL; pos_ptr = pos_ptr->next)
    {
        printf("%d ", pos_ptr->data);
    }
}

void print_list_tail_to_head(List* list)
{
    for (Node* pos_ptr = list->tail; pos_ptr != NULL; pos_ptr = pos_ptr->prev)
    {
        printf("%d ", pos_ptr->data);
    }
}

int main()
{


    return EXIT_SUCCESS;
}