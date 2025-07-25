#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;


typedef struct Stack
{
    Node* head;
    int elemcount;
} Stack;

void init_stack(Stack* stack)
{
    stack->head = NULL;
    stack->elemcount = 0;
}

void push(Stack* stack, int new_elem)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_elem;
    new_node->next = stack->head;

    stack->head = new_node;
    stack->elemcount++;
}

int pop(Stack* stack)
{
    if(stack->head == NULL)
    {
        printf("Stack underflow\n");
        return -1;
    }

    Node* temp = stack->head;
    int data = temp->data;

    stack->head = temp->next;
    free(temp);
    stack->elemcount--;

    return data;
}

int top(Stack* stack)
{
    if(stack->head == NULL)
    {
        printf("Stack is empty.\n");
        return -1;
    }

    return stack->head->data;
}

int is_empty(Stack* stack)
{
    return stack->elemcount == 0;
}

float evaluate_postfix(char* math_exp[], int size)
{
    Stack stack;
    init_stack(&stack);
    int result;

    for (int i = 0; i < size; i++)
    {
        if(math_exp[i][0] != '+' && math_exp[i][0] != '-' && math_exp[i][0] != '*' && math_exp[i][0] != '/')
        {
            float value = atof(math_exp[i]);
            push(&stack, value);
        }
        else
        {
            float op1 = pop(&stack);
            float op2 = pop(&stack);
            float res;

            if(strcmp(math_exp[i], "/") == 0)
            {
                res = op2 / op1;
            }
            else if(strcmp(math_exp[i], "*") == 0)
            {
                res = op2 * op1;
            }
            else if(strcmp(math_exp[i], "+") == 0)
            {
                res = op2 + op1;
            }
            else if(strcmp(math_exp[i], "-") == 0)
            {
                res = op2 - op1;
            }
            else
            {
                printf("Invalid value.\n");
                exit(EXIT_FAILURE);
            }

            push(&stack, res);
        }
    }

    return pop(&stack);
}

int main()
{
    char* math_exp[] = {"3", "6", "*", "4", "2", "/", "+"};
    int size = 7;
    printf("%.2f", evaluate_postfix(math_exp, size));

    return EXIT_SUCCESS;
}