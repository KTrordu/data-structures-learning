#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// ================================
// AVL TREE NODE STRUCTURE
// ================================

typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// ================================
// UTILITY FUNCTIONS
// ================================

int maximum(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

int getBalance(AVLNode* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(AVLNode* node) {
    if (node != NULL) {
        node->height = 1 + maximum(getHeight(node->left), getHeight(node->right));
    }
}

AVLNode* createNode(int data) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->height = 1;  // New node is at height 1
    node->left = NULL;
    node->right = NULL;
    return node;
}

// ================================
// ROTATION FUNCTIONS
// ================================

// Right Rotation (for LL case)
AVLNode* rotateRight(AVLNode* y) {
    printf("    Right rotation at node %d\n", y->data);
    
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    // Return new root
    return x;
}

// Left Rotation (for RR case)
AVLNode* rotateLeft(AVLNode* x) {
    printf("    Left rotation at node %d\n", x->data);
    
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    // Return new root
    return y;
}

// ================================
// AVL TREE OPERATIONS
// ================================

AVLNode* insert(AVLNode* node, int data) {
    // 1. Perform normal BST insertion
    if (node == NULL) {
        printf("  Inserting %d as new leaf\n", data);
        return createNode(data);
    }

    if (data < node->data) {
        printf("  Going left from %d\n", node->data);
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        printf("  Going right from %d\n", node->data);
        node->right = insert(node->right, data);
    } else {
        // Duplicate keys not allowed
        printf("  Duplicate key %d ignored\n", data);
        return node;
    }

    // 2. Update height of current node
    updateHeight(node);

    // 3. Get balance factor
    int balance = getBalance(node);
    printf("  Node %d: height=%d, balance=%d\n", 
           node->data, node->height, balance);

    // 4. If unbalanced, there are 4 cases

    // Left Left Case (LL)
    if (balance > 1 && data < node->left->data) {
        printf("  LL imbalance detected at node %d\n", node->data);
        return rotateRight(node);
    }

    // Right Right Case (RR)
    if (balance < -1 && data > node->right->data) {
        printf("  RR imbalance detected at node %d\n", node->data);
        return rotateLeft(node);
    }

    // Left Right Case (LR)
    if (balance > 1 && data > node->left->data) {
        printf("  LR imbalance detected at node %d\n", node->data);
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case (RL)
    if (balance < -1 && data < node->right->data) {
        printf("  RL imbalance detected at node %d\n", node->data);
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Return unchanged node
    return node;
}

AVLNode* search(AVLNode* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    printf("  Searching %d: current node %d\n", key, root->data);

    if (key < root->data) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// ================================
// TREE VISUALIZATION
// ================================

void printTreeStructure(AVLNode* root, int space) {
    const int COUNT = 4;
    if (root == NULL) return;

    space += COUNT;
    printTreeStructure(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d(h:%d,bf:%d)\n", root->data, root->height, getBalance(root));

    printTreeStructure(root->left, space);
}

void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d(bf:%d) ", root->data, getBalance(root));
        inorderTraversal(root->right);
    }
}

void preorderTraversal(AVLNode* root) {
    if (root != NULL) {
        printf("%d(h:%d) ", root->data, root->height);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// ================================
// VALIDATION FUNCTIONS
// ================================

bool isAVL(AVLNode* root) {
    if (root == NULL) return true;

    int balance = getBalance(root);
    if (abs(balance) > 1) {
        printf("Violation at node %d: balance = %d\n", root->data, balance);
        return false;
    }

    return isAVL(root->left) && isAVL(root->right);
}

int countNodes(AVLNode* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// ================================
// DEMONSTRATION FUNCTIONS
// ================================

void demonstrateRotations() {
    printf("\n=== ROTATION DEMONSTRATIONS ===\n");

    // LL Case Demo
    printf("\n1. LEFT-LEFT (LL) CASE:\n");
    AVLNode* llRoot = NULL;
    printf("Inserting: 30, 20, 10 (creates LL imbalance)\n");
    llRoot = insert(llRoot, 30);
    llRoot = insert(llRoot, 20);
    llRoot = insert(llRoot, 10);
    printf("Result after right rotation:\n");
    printTreeStructure(llRoot, 0);

    // RR Case Demo
    printf("\n2. RIGHT-RIGHT (RR) CASE:\n");
    AVLNode* rrRoot = NULL;
    printf("Inserting: 10, 20, 30 (creates RR imbalance)\n");
    rrRoot = insert(rrRoot, 10);
    rrRoot = insert(rrRoot, 20);
    rrRoot = insert(rrRoot, 30);
    printf("Result after left rotation:\n");
    printTreeStructure(rrRoot, 0);

    // LR Case Demo
    printf("\n3. LEFT-RIGHT (LR) CASE:\n");
    AVLNode* lrRoot = NULL;
    printf("Inserting: 30, 10, 20 (creates LR imbalance)\n");
    lrRoot = insert(lrRoot, 30);
    lrRoot = insert(lrRoot, 10);
    lrRoot = insert(lrRoot, 20);
    printf("Result after double rotation:\n");
    printTreeStructure(lrRoot, 0);

    // RL Case Demo
    printf("\n4. RIGHT-LEFT (RL) CASE:\n");
    AVLNode* rlRoot = NULL;
    printf("Inserting: 10, 30, 20 (creates RL imbalance)\n");
    rlRoot = insert(rlRoot, 10);
    rlRoot = insert(rlRoot, 30);
    rlRoot = insert(rlRoot, 20);
    printf("Result after double rotation:\n");
    printTreeStructure(rlRoot, 0);
}

void demonstrateComplexInsertions() {
    printf("\n=== COMPLEX AVL TREE CONSTRUCTION ===\n");
    
    AVLNode* root = NULL;
    int values[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35};
    int n = sizeof(values) / sizeof(values[0]);

    printf("Building AVL tree with values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n\n");

    for (int i = 0; i < n; i++) {
        printf("--- Inserting %d ---\n", values[i]);
        root = insert(root, values[i]);
        
        printf("Current tree structure:\n");
        printTreeStructure(root, 0);
        
        printf("Inorder: ");
        inorderTraversal(root);
        printf("\n");
        
        printf("AVL property: %s\n", isAVL(root) ? "Valid" : "Invalid");
        printf("\n");
    }

    printf("=== FINAL AVL TREE ===\n");
    printf("Tree structure:\n");
    printTreeStructure(root, 0);
    
    printf("\nInorder traversal: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("Tree height: %d\n", getHeight(root));
    printf("Total nodes: %d\n", countNodes(root));
    printf("AVL property: %s\n", isAVL(root) ? "Valid" : "Invalid");

    // Search demonstrations
    printf("\n=== SEARCH DEMONSTRATIONS ===\n");
    int searchValues[] = {27, 100, 5, 75};
    for (int i = 0; i < 4; i++) {
        printf("Searching for %d:\n", searchValues[i]);
        AVLNode* found = search(root, searchValues[i]);
        if (found) {
            printf("  Found %d\n", found->data);
        } else {
            printf("  Not found\n");
        }
    }
}

// ================================
// MAIN FUNCTION
// ================================

int main() {
    printf("AVL TREE COMPLETE IMPLEMENTATION\n");
    printf("=================================\n");

    // Demonstrate all rotation types
    demonstrateRotations();

    // Demonstrate complex tree construction
    demonstrateComplexInsertions();

    // Performance comparison
    printf("\n=== PERFORMANCE ANALYSIS ===\n");
    printf("AVL Tree guarantees:\n");
    printf("  • Search:  O(log n)\n");
    printf("  • Insert:  O(log n)\n");
    printf("  • Delete:  O(log n)\n");
    printf("  • Height:  O(log n)\n\n");

    printf("Compared to unbalanced BST worst case:\n");
    printf("  • Search:  O(n)\n");
    printf("  • Insert:  O(n)\n");
    printf("  • Delete:  O(n)\n");
    printf("  • Height:  O(n)\n\n");

    printf("Balance Factor Rules:\n");
    printf("  • -1: Right subtree taller\n");
    printf("  •  0: Equal height subtrees\n");
    printf("  • +1: Left subtree taller\n");
    printf("  • ±2: ROTATION REQUIRED!\n\n");

    printf("Rotation Cases:\n");
    printf("  • LL → Right Rotation\n");
    printf("  • RR → Left Rotation\n");
    printf("  • LR → Left-Right Double Rotation\n");
    printf("  • RL → Right-Left Double Rotation\n");

    return 0;
}