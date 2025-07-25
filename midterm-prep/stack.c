#include <stdio.h>
#include <stdlib.h>

#define LIMIT 100

typedef struct stack
{
    int data[LIMIT];
    int elemcount;
} Stack;

void init_stack(Stack* stack)
{
    stack->elemcount = 0;
}

void push(Stack* stack, int new_elem)
{
    if (stack->elemcount < LIMIT)
    {
        stack->data[stack->elemcount] = new_elem;
        stack->elemcount++;
    }
    else
    {
        printf("Stack overflow.\n");
    }
}

int pop(Stack* stack)
{
    if (stack->elemcount > 0)
    {
        stack->elemcount--;
        return stack->data[stack->elemcount];
    }
    else
    {
        printf("Stack underflow.\n");
        return -1;
    }
}

int top(Stack* stack)
{
    if(stack->elemcount > 0)
    {
        return stack->data[stack->elemcount - 1];
    }
    else
    {
        printf("Stack is empty.\n");
        return -1;
    }
}

int is_empty(Stack* stack)
{
    return stack->elemcount == 0;
}

int main()
{
    

    return EXIT_SUCCESS;
}