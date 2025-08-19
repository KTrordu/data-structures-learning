#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
} Node;

void preorder(Node* ptr)
{
    if(ptr)
    {
        printf("%d\n", ptr->data);
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void inorder(Node* ptr)
{
    if(ptr)
    {
        inorder(ptr->left);
        printf("%d\n", ptr->data);
        inorder(ptr->right);
    }
}

void postorder(Node* ptr)
{
    if(ptr)
    {
        postorder(ptr->left);
        postorder(ptr->right);
        printf("%d\n", ptr->data);
    }
}

Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* node, int data)
{
    if(node == NULL) return createNode(data);
    if(data < node->data) node->left = insert(node->left, data);
    else if(data > node->data) node->right = insert(node->right, data);
    return node;
}

bool search(Node* node, int key)
{
    if(node == NULL) return false;
    printf("Current Node: %d\n", node->data);

    if(node->data == key) return true;
    if(key < node->data) return search(node->left, key);
    return search(node->right, key);
}

Node* minValueNode(Node* node)
{
    Node* current = node;
    while(current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

Node* maxValueNode(Node* node)
{
    Node* current = node;
    while(current && current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

int main()
{
    Node* root = NULL;

    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 6);
    root = insert(root, 8);

    inorder(root);
    preorder(root);
    postorder(root);
    search(root, 4);

    printf("Minimum value in the tree: %d\n", minValueNode(root)->data);
    printf("Maximum value in the tree: %d\n", maxValueNode(root)->data);

    return EXIT_SUCCESS;
}