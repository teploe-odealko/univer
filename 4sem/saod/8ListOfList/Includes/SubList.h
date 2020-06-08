#pragma once
#define SubList_h

struct NodeNum
{
    NodeNum* right;
    NodeNum* left;
    int data;
};

struct SubList
{
private:
    int currentSize = 0;
    
public:
    NodeNum* pHead;
    int id;
    SubList(int);
    SubList();
    NodeNum *findDirect(int);
    bool addAfter(int, int);
    bool addBefore(int, int);
    void pushBack(int);
    int getSize();
    bool removeItem(int);
    bool isEmpty();
    ~SubList();
};

