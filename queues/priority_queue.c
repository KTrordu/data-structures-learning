#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PQ_SIZE 100

typedef struct
{
    int priority;
    char task_name[50];
} Task;

typedef struct
{
    Task queue[100];
    int size;
} PriorityQueue;

typedef int (*Comparator)(Task, Task);

void init_queue(PriorityQueue *pq) { pq->size = 0; }

int isEmpty(PriorityQueue *pq)
{
    return pq->size == 0;
}

void swap(Task *a, Task *b)
{
    Task temp = *a;
    *a = *b;
    *b = temp;
}

int min_comparator(Task t1, Task t2)
{
    if(t1.priority < t2.priority) return -1;
    else if (t1.priority > t2.priority) return 1;
    else return 0;
}

int max_comparator(Task t1, Task t2)
{
    if(t1.priority > t2.priority) return -1;
    else if (t1.priority < t2.priority) return 1;
    else return 0;
}

void print_queue(PriorityQueue *pq)
{
    printf("Priority Queue:\n");
    for (int i = 0; i < pq->size; i++)
    {
        printf("Task: %s, Priority: %d\n", pq->queue[i].task_name, pq->queue[i].priority);
    }
    printf("\n");
}

void insert(PriorityQueue *pq, int priority, const char* task_name, Comparator cmp)
{
    if(pq->size >= PQ_SIZE)
    {
        printf("Priority queue is full.\n");
        return;
    }

    Task new_task;
    new_task.priority = priority;
    strncpy(new_task.task_name, task_name, sizeof(task_name));
    new_task.task_name[sizeof(task_name) - 1] = '\0';

    pq->queue[pq->size] = new_task;
    int i = pq->size;
    pq->size++;

    while(i > 0 && cmp(pq->queue[i - 1], pq->queue[i]) > 0)
    {
        swap(&pq->queue[i - 1], &pq->queue[i]);
        i -= 1;
    }
}

Task remove_top(PriorityQueue *pq)
{
    if(pq->size <= 0)
    {
        printf("Priority queue is empty.\n");
        exit(1);
    }

    Task top_task = pq->queue[0];
    pq->size--;

    for (int i = 0; i < pq->size; i++)
    {
        swap(&pq->queue[i], &pq->queue[i + 1]);
    }
    return top_task;
}

int main()
{
    PriorityQueue pq;
    init_queue(&pq);

    insert(&pq, 3, "Low priority task", min_comparator);
    insert(&pq, 1, "High priority task", min_comparator);
    insert(&pq, 2, "Medium priority task", min_comparator);
    insert(&pq, 4, "Very low priority task", min_comparator);
    insert(&pq, 5, "Very low priority task", min_comparator);

    print_queue(&pq);

    printf("Removing highest-priority task: %s\n", remove_top(&pq));
    print_queue(&pq);
}
