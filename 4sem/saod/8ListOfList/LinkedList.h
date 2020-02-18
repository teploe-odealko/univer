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
    NodeLL<T>* findDirect(T searchBy){
        NodeLL<T>* pCurrent = pHead->right;
        while ((pCurrent != pHead) && (pCurrent->data)!=searchBy) {
            pCurrent = pCurrent->right;
        }
        return pCurrent;
    };

    NodeLL<T>* findBackward(T searchBy){
        NodeLL<T>* pCurrent = pHead->left;
        while ((pCurrent != pHead) && (pCurrent->data)!=searchBy) {
            pCurrent = pCurrent->left;
        }
        return pCurrent;
    };

public:
    LinkedList();
    bool addAfter(T, T) ;
    bool addBefore(T, T);
    void pushBack(T);
    void showAllDirect();
    void showAllBackward();
    bool removeItem(T);
    void printSize();
    
    bool isEmpty();
    ~LinkedList();

};

#include "LinkedList.tpp"
