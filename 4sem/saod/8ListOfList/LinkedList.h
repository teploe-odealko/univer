#pragma once
#define LinkedList_h

template <typename T> 
struct NodeLL
{
    NodeLL<T>* right;
    NodeLL<T>* left;
    T data;
};

template <typename T>
class LinkedList
{
private:
    NodeLL<T>* pHead;
    int currentSize = 0;



public:
    LinkedList();
    NodeLL<T>* findDirect(T);
    bool addAfter(T, T) ;
    bool addBefore(T, T);
    void pushBack(T);
    void showAllDirect();
    void showAllBackward();
    bool removeItem(T);
    void removeAll();
    void printSize();
    
    bool isEmpty();
    ~LinkedList();

};

#include "LinkedList.tpp"
