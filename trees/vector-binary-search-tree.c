#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct
{
    int* tree;
    int capacity;
} ArrayBST;

void create(ArrayBST* bst, int capacity)
{
    bst->capacity = capacity;
    bst->tree = (int*)malloc(capacity * sizeof(int));

    if(bst->tree == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < capacity; i++)
    {
        bst->tree[i] = INT_MIN;
    }
}

void insert(ArrayBST* bst, int value)
{
    if(bst->tree[0] == INT_MIN)
    {
        bst->tree[0] = value;
        return;
    }

    int index = 0;
    while(index < bst->capacity)
    {
        if(bst->tree[index] == INT_MIN)
        {
            bst->tree[index] = value;
            return;
        }
        else if(value < bst->tree[index])
        {
            index = 2 * index + 1;
        }
        else
        {
            index = 2 * index + 2;
        }
    }

    printf("Tree capacity exceeded\n");
}

void print_as_array(ArrayBST* bst)
{
    printf("Tree elements: ");
    for(int i = 0; i < bst->capacity; i++)
    {
        if(bst->tree[i] == INT_MIN) printf("_ ");
        else printf("%d ", bst->tree[i]);
    }
    printf("\n");
}

void preorder(ArrayBST* bst, int index)
{
    if(index >= bst->capacity || bst->tree[index] == INT_MIN) return;

    printf("%d ", bst->tree[index]);
    preorder(bst, 2 * index + 1);
    preorder(bst, 2 * index + 2);
}

int main()
{
    ArrayBST bst;

    create(&bst, 10);

    insert(&bst, 5);
    insert(&bst, 3);
    insert(&bst, 7);
    insert(&bst, 2);
    insert(&bst, 4);
    insert(&bst, 6);
    insert(&bst, 8);

    print_as_array(&bst);
    printf("Preorder traversal: ");
    preorder(&bst, 0);
    free(bst.tree);

    return EXIT_SUCCESS;
}