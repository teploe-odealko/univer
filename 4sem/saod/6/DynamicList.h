#pragma once
#define DynamicList_h

struct Node
{
    Node* next;
    int data;
};


class DynamicList
{
private:
    Node* last;
    Node* pHead;
    Node* sp = nullptr;
    int currentSize = 0;

public:
    DynamicList();
    bool addAfter(int, int) ;
    bool addBefore(int, int);
    void pushBack(int);
    void showAll();
    void showStack();
    bool removeItem(int);
    void printSize();
    
    bool isEmpty();
    ~DynamicList();

};

