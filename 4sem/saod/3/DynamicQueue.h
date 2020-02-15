#pragma once
#define DynamicQueue_h

struct Node
{
    Node *next = nullptr;
    char data;
};


class DynamicQueue
{
private:
    Node *first;
    Node *last;
    int currentSize = 0;

public:
    DynamicQueue();
    void addItem(char new_item);
    void showAll();
    void removeItem();
    void printSize();
    bool isEmpty();
    ~DynamicQueue();

};

