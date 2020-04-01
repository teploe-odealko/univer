#pragma once
#define DynamicList_h

template<typename T>
struct Node
{
    Node<T>* next;
    T data;
};

template <typename T>
class DynamicList
{
private:
    Node<T>* last;
    Node<T>* pHead;
    Node<T>* sp = nullptr;
    int currentSize = 0;

public:
    DynamicList();
    void pushBack(T);
    void showAll();
    void showStack();
    bool removeItem(int);
    int getSize(){return currentSize;}
    T* getItemByIndex(int);
    void printSize();
    bool isEmpty();
    ~DynamicList();

};

#include "DynamicList.tpp"
