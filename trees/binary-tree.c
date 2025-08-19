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

void preorder(TreeNode* ptr)
{
    if(ptr)
    {
        printf("%d\n", ptr->data);
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

void inorder(TreeNode* ptr)
{
    if(ptr)
    {
        inorder(ptr->left);
        printf("%d\n", ptr->data);
        inorder(ptr->right);
    }
}

void postorder(TreeNode* ptr)
{
    if(ptr)
    {
        postorder(ptr->left);
        postorder(ptr->right);
        printf("%d\n", ptr->data);
    }
}

int preorder_sum(TreeNode* ptr)
{
    if(ptr)
    {
        return preorder_sum(ptr->left) + preorder_sum(ptr->right) + ptr->data;
    }
}

int preorder_sum_ref(TreeNode* ptr, int* sum)
{
    if(ptr)
    {
        *sum += ptr->data;
        preorder_sum_ref(ptr->left, sum);
        preorder_sum_ref(ptr->right, sum);
    }
}

int inorder_sum(TreeNode* ptr)
{
    if(ptr)
    {
        return inorder_sum(ptr->left) + ptr->data + inorder_sum(ptr->right);
    }
}

int postorder_sum(TreeNode* ptr)
{
    if(ptr)
    {
        return ptr->data + postorder_sum(ptr->left) + postorder_sum(ptr->right);
    }
}

int preorder_max(TreeNode* ptr)
{
    if(ptr == NULL) return INT_MIN;
    int leftMax = preorder_max(ptr->left);
    int rightMax = preorder_max(ptr->right);
    int maxVal = ptr->data;
    if(leftMax > maxVal) maxVal = leftMax;
    if(rightMax > maxVal) maxVal = rightMax;
    return maxVal;
}

int preorder_max_ref(TreeNode* ptr, int* max)
{
    if(ptr)
    {
        if(ptr->data > *max)
        {
            *max = ptr->data;
        }
        preorder_max_ref(ptr->left, max);
        preorder_max_ref(ptr->right, max);
    }
}

int preorder_min(TreeNode* ptr)
{
    if(ptr == NULL) return INT_MAX;
    int leftMin = preorder_min(ptr->left);
    int rightMin = preorder_min(ptr->right);
    int minVal = ptr->data;
    if(leftMin < minVal) minVal = leftMin;
    if(rightMin < minVal) minVal = rightMin;
    return minVal;
}

int preorder_min_ref(TreeNode* ptr, int* min)
{
    if(ptr)
    {
        if(ptr->data < *min)
        {
            *min = ptr->data;
        }
        preorder_min_ref(ptr->left, min);
        preorder_min_ref(ptr->right, min);
    }
}

int count_nodes(TreeNode* ptr)
{
    if(ptr == NULL) return 0;
    return 1 + count_nodes(ptr->left) + count_nodes(ptr->right);
}

int preorder_count_ref(TreeNode* ptr, int* count)
{
    if(ptr)
    {
        (*count)++;
        preorder_count_ref(ptr->left, count);
        preorder_count_ref(ptr->right, count);
    }
}

float preorder_average(TreeNode* ptr)
{
    int sum = preorder_sum(ptr);
    int nodeCount = count_nodes(ptr);
    if (nodeCount == 0) return 0;
    return (float)sum / nodeCount;
}

int depth(TreeNode* node)
{
    if(node->parent == NULL) return 0;
    else return 1 + depth(node->parent);
}

int height(TreeNode* node)
{
    if(node == NULL) return 0;
    else if(node->left == NULL) return height(node->right) + 1;
    else if (node->right == NULL) return height(node->left) + 1;
    else
    {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        if(leftHeight > rightHeight) return leftHeight + 1;
        else return rightHeight + 1;
    }
}

int main()
{
    TreeNode* root = createNodeWithParent(1, NULL);
    root->left = createNodeWithParent(2, root);
    root->right = createNodeWithParent(3, root);
    root->left->left = createNodeWithParent(4, root->left);
    root->left->right = createNodeWithParent(5, root->left);

    printf("%d\n", root->left->right->parent->parent->data);

    int sum = 0;
    preorder_sum_ref(root, &sum);

    int max = INT_MIN;
    preorder_max_ref(root, &max);

    int min = INT_MAX;
    preorder_min_ref(root, &min);

    int count = 0;
    preorder_count_ref(root, &count);

    int avg = preorder_average(root);

    int dep = depth(root->left->left);
    int hig = height(root->left);

    printf("%d\n%d\n%d\n%d\n%d\n%d\n%d\n", sum, max, min, count, avg, dep, hig);

    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);

    return EXIT_SUCCESS;
}