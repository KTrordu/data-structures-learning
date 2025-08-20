#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node* rightparent;
    Node* leftparent;
};

Node* createNode(int data)
{
    Node* node = new Node;
    node->data = data;
    node-> left = nullptr;
    node-> right = nullptr;
    node-> rightparent = nullptr;
    node-> leftparent = nullptr;

    return node;
}

Node* create_binomial_graph(int depth)
{
    if(depth <= 0) return NULL;

    vector<vector<Node*>> grid(depth);
    grid[0].push_back(createNode(1));

    for(int i = 1; i < depth; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            Node* node = createNode(0);

            if(j < i)
            {
                node->rightparent = grid[i-1][j];
                grid[i-1][j]->right = node;
            }
            if(j > 0)
            {
                node->leftparent = grid[i-1][j-1];
                grid[i-1][j-1]->left = node;
            }

            if(node->rightparent)
            {
                node->data += node->rightparent->data;
            }
            if(node->leftparent)
            {
                node->data += node->leftparent->data;
            }

            grid[i].push_back(node);
        }
    }

    return grid[0][0];
}

vector<int> get_coefficients(Node* root, int depth)
{
    Node* ptr = root;
    vector<int> result;

    for(int i = 0; i < depth; i++)
    {
        ptr = ptr->left;
    }

    while(ptr != NULL)
    {
        result.push_back(ptr->data);

        if(ptr->leftparent != NULL)
        {
            ptr = ptr->leftparent->right;
        }
        else
        {
            ptr = NULL;
        }
    }

    return result;
}

int main()
{
    Node* binomial_tree = create_binomial_graph(5);

    vector<int> result =  get_coefficients(binomial_tree, 4);

    for(int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }

    return 0;
}