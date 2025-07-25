#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

typedef struct Queue
{
    Node* head;
    Node* tail;
    int elemcount;
} Queue;

void init_queue(Queue* q)
{
    q->head = NULL;
    q->tail = NULL;
    q->elemcount = 0;
}

void enqueue(Queue* q, int new_elem)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_elem;
    new_node->next = NULL;

    if(q->tail != NULL)
    {
        q->tail->next = new_node;
    }
    q->tail = new_node;

    if(q->head == NULL)
    {
        q->head = new_node;
    }

    q->elemcount++;
}

void dequeue(Queue* q)
{
    if(q->head == NULL)
    {
        printf("Queue is empty.\n");
        return;
    }

    Node* temp = q->head;
    q->head = q->head->next;
    if(q->head == NULL) q->tail = NULL;

    free(temp);
    q->elemcount--;
}

int front(Queue* q)
{
    if(q->head == NULL)
    {
        printf("Queue is empty.\n");
        return -1;
    }
    return q->head->data;
}

int main()
{


    return EXIT_SUCCESS;
}