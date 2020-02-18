#pragma once
#define LinkedList_h

struct Node
{
    Node* right;
    Node* left;
    int data;
};


class LinkedList
{
private:
    Node* pHead;
    int currentSize = 0;
    Node* findDirect(int searchBy){
        Node* pCurrent = pHead->right;
        while ((pCurrent != pHead) && (pCurrent->data)!=searchBy) {
            pCurrent = pCurrent->right;
        }
        return pCurrent;
    };

    Node* findBackward(int searchBy){
        Node* pCurrent = pHead->left;
        while ((pCurrent != pHead) && (pCurrent->data)!=searchBy) {
            pCurrent = pCurrent->left;
        }
        return pCurrent;
    };

public:
    LinkedList();
    bool addAfter(int, int) ;
    bool addBefore(int, int);
    void pushBack(int);
    void showAllDirect();
    void showAllBackward();
    bool removeItem(int);
    void printSize();
    
    bool isEmpty();
    ~LinkedList();

};

