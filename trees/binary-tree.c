#include "stdio.h"
#include "stdlib.h"

typedef struct treeNode TreeNode;

typedef struct treeNode
{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
} TreeNode;

TreeNode* createNodeWithParent(int data, TreeNode* parent)
{
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}


int main()
{
    TreeNode* root = createNodeWithParent(1, NULL);
    root->left = createNodeWithParent(2, root);
    root->right = createNodeWithParent(3, root);
    root->left->left = createNodeWithParent(4, root->left);
    root->left->right = createNodeWithParent(5, root->left);

    printf("%d\n", root->left->right->parent->parent->data);

    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);

    return EXIT_SUCCESS;
}