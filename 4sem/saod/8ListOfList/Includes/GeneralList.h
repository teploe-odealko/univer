#pragma once
#include "SubList.h"
#define GeneralList_h

struct NodeLL
{
    NodeLL* right;
    NodeLL* left;
    SubList* data;
};

class GeneralList
{
private:
    int currentSize = 0;
    
public:
    NodeLL* pHead;
    int id;
    GeneralList();
    NodeLL *findSubList(int);
    bool addAfter(SubList*, int);
    bool addBefore(SubList*, int);
    void pushBack(SubList*);
    int getSize();
    void showAllDirect();
    bool removeItem(int);
    bool isEmpty();
    ~GeneralList();

};

