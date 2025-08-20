#include "stdio.h"
#include "stdlib.h"

typedef struct Node
{
    char character;
    int frequency;
    struct Node *left, *right;
} Node;

Node* createNode(char character, int frequency)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

void findTwoSmallest(Node* nodes[], int size, int* smallest, int* secondSmallest)
{
    *smallest = -1;
    *secondSmallest = -1;

    for(int i = 0; i < size; i++)
    {
        if(nodes[i] != NULL)
        {
            if(*smallest == -1 || nodes[i]->frequency < nodes[*smallest]->frequency)
            {
                *secondSmallest = *smallest;
                *smallest = i;
            }
            else if(*secondSmallest == -1 || nodes[i]->frequency < nodes[*secondSmallest]->frequency)
            {
                *secondSmallest = i;
            }
        }
    }
}

Node* buildHuffmanTree(char characters[], int frequencies[], int size)
{
    Node** nodes = (Node**)malloc(size * sizeof(Node*));

    for(int i = 0; i < size; i ++)
    {
        nodes[i] = createNode(characters[i], frequencies[i]);
    }

    for(int count = 1; count < size; count++)
    {
        int smallest, secondSmallest;
        findTwoSmallest(nodes, size, &smallest, &secondSmallest);

        Node* newNode = createNode('\0', nodes[smallest]->frequency + nodes[secondSmallest]->frequency);
        newNode->left = nodes[smallest];
        newNode->right = nodes[secondSmallest];

        nodes[smallest] = newNode;
        nodes[secondSmallest] = NULL;
    }

    for(int i = 0; i < size; i++)
        {
            if(nodes[i] != NULL)
            {
                return nodes[i];
            }
        }
    return NULL;
}

void printHuffmanTree(Node* root, char* code, int top)
{
    if(root->left)
    {
        code[top] = '0';
        printHuffmanTree(root->left, code, top + 1);
    }
    if(root->right)
    {
        code[top] = '1';
        printHuffmanTree(root->right, code, top + 1);
    }
    if(!root->left && !root->right)
    {
        code[top] = '\0';
        printf("Character: %c, Code: %s\n", root->character, code);
    }
}

int main()
{
    char characters[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int frequencies[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(characters) / sizeof(characters[0]);

    Node* root = buildHuffmanTree(characters, frequencies, size);

    char code[100];
    printHuffmanTree(root, code, 0);

    return EXIT_SUCCESS;
}