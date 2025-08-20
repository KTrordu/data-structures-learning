#include <iostream>

struct Node
{
    int data;
    Node *next = NULL;
};

struct CircularList
{
    Node *cursor = NULL;
    int elemcount = 0;
    int &front() { return cursor->next->data; }
    int &back() { return cursor->data; }
    int length() { return this->elemcount; }
    void addFront(int);
    void advance() { cursor = cursor->next; }
    int &get(int);
};

void CircularList::addFront(int new_element)
{
    Node *newNode = new Node;
    newNode->data = new_element;

    if (this->cursor == NULL)
    {
        newNode->next = newNode;
        cursor = newNode;
    }
    else
    {
        newNode->next = cursor->next;
        cursor->next = newNode;
        advance();
    }
    elemcount++;
}

int &CircularList::get(int index)
{
    while (index < 0) index += index + length();

    Node* iterator = cursor;

    for(int i = 0; i < index; i++) iterator = iterator->next;
    return iterator ->data;
}

int main()
{

    return 0;
}