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

    int currentSize = 0;
    
    
    
public:
    NodeLL<T>* pHead;
    int id;
    LinkedList();
    LinkedList(int);
    NodeLL<LinkedList<int>> *findSubList(int);
    NodeLL<int> *findItem(int);
    bool addAfter(T&, int);
    bool addBefore(T&, int);
    void pushBack(T&, int);
    void pushBack(T&);
    int getSize();
    void showAllDirect();
    void showAllDirect(int);
    void showAllBackward();
    bool removeItem(T);
    void removeAll();
    bool isEmpty();
    ~LinkedList();

};

#include "LinkedList.tpp"
