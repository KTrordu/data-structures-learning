#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node* parent;
    bool visited = false;
};

bool is_loop(Node* root)
{
    if(root == nullptr) return false;

    if (root->visited == true)
    {
        cout << "There is a loop." << endl;
        return true;
    }

    root->visited = true;
    bool left_hasloop = is_loop(root->left);
    bool right_has_loop = is_loop(root->right);

    return left_hasloop || right_has_loop;
}

int main()
{


    return 0;
}