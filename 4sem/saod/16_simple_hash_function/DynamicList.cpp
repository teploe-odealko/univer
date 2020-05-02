#include "DynamicList.h"
#include <iostream>
using namespace std;


DynamicList::DynamicList() {
    pHead = new Node();
    pHead->next = nullptr;
    last = pHead;
}


DynamicList::~DynamicList() {
    Node *pTemp;
    while (pTemp != nullptr)
    {
        pTemp = pHead->next;
        delete pHead;
        pHead = pTemp;
    }
    delete pHead;
}

void DynamicList::pushBack(int new_item) {
    Node* pTemp = new Node();
    pTemp->data =  new_item;
    pTemp->next = nullptr;
    last->next = pTemp;
    last = pTemp;
    // currentSize++;
}




