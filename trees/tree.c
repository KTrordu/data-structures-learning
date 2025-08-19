#include "stdio.h"
#include "stdlib.h"

typedef struct treeNode TreeNode;
typedef struct listNode ListNode;

typedef struct treeNode
{
    int data;
    TreeNode* parent;
    ListNode* children;
} TreeNode;

typedef struct listNode
{
    TreeNode* child;
    ListNode* next;
} ListNode;

void addFront(TreeNode* parent, TreeNode* child)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->child = child;
    newNode->next = parent->children;
    parent->children = newNode;
}

void printTree(TreeNode* tree)
{
    if (tree == NULL) return;

    printf("%d\n", tree->data);
    ListNode* ptr = tree->children;
    while(ptr != NULL)
    {
        printTree(ptr->child);
        ptr = ptr->next;
    }
}

int main()
{
    TreeNode head;
    head.parent = NULL;
    head.data = 1;
    head.children = NULL;

    for (int i = 2; i <5; i++)
    {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = i;
        newNode->parent = &head;
        newNode->children = NULL;
        addFront(&head, newNode);
    }

    TreeNode* firstChild = head.children->child;
    for(int i = 5; i < 7; i++)
    {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = i;
        newNode->parent = firstChild;
        newNode->children = NULL;
        addFront(firstChild, newNode);
    }

    printTree(&head);

    return EXIT_SUCCESS;
}