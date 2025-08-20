#include <iostream>

struct Node
{
    Node* next = NULL;
    Node* left = NULL;
    Node* right = NULL;
};

Node* createBridge(int length)
{
    Node* middle = new Node;
    Node* left = new Node;
    Node* right = new Node;

    middle->left = left;
    middle->right = right;
    left->right = middle;
    right->left = middle;

    Node* start = middle;

    for(int i = 1; i < length; i++)
    {
        middle->next = new Node;
        left->next = new Node;
        right->next = new Node;

        middle->next->left = left->next;
        middle->next->right = right->next;
        left->next->right = middle->next;
        right->next->left = middle->next;

        middle = middle->next;
        left = left->next;
        right = right->next;
    }

    return start;
}

Node* advance(Node* start, int direction)
{
    if(direction == 1) return start->left;
    else if(direction == 2) return start->next;
    else return start->right;
}

int main()
{
    srand (time(NULL));
    Node* start = createBridge(8);

    while(start->next != NULL)
    {
        int direction = rand() % 3 + 1;
        start = advance(start, direction);
        if(start == NULL)
        {
            std::cout<<"You've fallen from the bridge!"<<std::endl;
            return -1;
        }
    }
    std::cout<<"You've successfully crossed the bridge!"<<std::endl;

    return 0;
}