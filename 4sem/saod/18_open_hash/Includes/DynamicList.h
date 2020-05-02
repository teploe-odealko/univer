#pragma once
#define DynamicList_h
#include <string>
struct Node
{
    Node* next;
    std::string data;
};


class DynamicList
{
private:
    Node* last;
    
    // int currentSize = 0;

public:
    Node* pHead;
    DynamicList();
    void pushBack(std::string);
    ~DynamicList();

};

