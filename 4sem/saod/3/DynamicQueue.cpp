#include "DynamicQueue.h"
#include <iostream>
using namespace std;


DynamicQueue::DynamicQueue() {
    first = new Node();
    last = first;
}


DynamicQueue::~DynamicQueue() {

}

void DynamicQueue::addItem(char new_item) {
    Node *pTemp = new Node();
    pTemp -> data = new_item;
    last -> next = pTemp;
    last = pTemp;
    currentSize++;
}

void DynamicQueue::showAll() {
    Node *current = first -> next;
    cout << "\n----------------\nFIRST\n\n";
    while (current != nullptr)
    {
        cout << current -> data << endl;
        current = current -> next;
        
    }
    cout << "\nLAST\n----------------\n";
}

void DynamicQueue::removeItem() {
    if (!isEmpty()){
        Node* pTemp = first -> next;
        first -> next = pTemp -> next;
        if (first -> next == nullptr){
            last = first;
        }
        delete pTemp;
    }



}

void DynamicQueue::printSize() {
    cout << "\nSize of stack: " << currentSize << endl;
}

bool DynamicQueue::isEmpty() {
    if (first -> next == nullptr) return true;
    else return false;
}
