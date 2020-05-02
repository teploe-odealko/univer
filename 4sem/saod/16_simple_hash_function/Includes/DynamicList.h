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
    
    // int currentSize = 0;

public:
    Node* pHead;
    DynamicList();
    void pushBack(int);
    ~DynamicList();

};

