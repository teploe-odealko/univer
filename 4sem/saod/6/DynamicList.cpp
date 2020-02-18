#include "DynamicList.h"
#include <iostream>
using namespace std;


DynamicList::DynamicList() {
    pHead = new Node();
    pHead->next = nullptr;
    last = pHead;
}


DynamicList::~DynamicList() {
    
}

void DynamicList::pushBack(int new_item) {
    Node* pTemp = new Node();
    pTemp->data =  new_item;
    pTemp->next = nullptr;
    last->next = pTemp;
    last = pTemp;
    currentSize++;
}

void DynamicList::showAll() {
    Node *current = pHead -> next;
    cout << "\n----------------\nFIRST\n\n";

    while (current != nullptr)
    {
        cout << current->data << endl;
        current = current -> next;
        
    }

    cout << "\nLAST\n----------------\n";
}

bool DynamicList::removeItem(int item_to_remove) {
    Node* pPrev = pHead; 
    Node* pCurrent = pHead -> next;

    while ((pCurrent != nullptr) && (pCurrent->data)!=item_to_remove) {
        pPrev = pCurrent;
        pCurrent = pCurrent->next;
    }
    if (pCurrent == nullptr){ // Если заданного элемента нет в списке
        return false;
    } else {  // Помещение удаляемого объекта в вспомогательный стек
        pPrev->next = pCurrent->next;
        if (pPrev->next == nullptr){
            last = pPrev;
        }
        pCurrent->next = sp;
        sp = pCurrent;
        currentSize--;
        return true;
    }

}

void DynamicList::showStack(){
    Node *current = sp;
    cout << "\n----------------\nUp of stack\n\n";
    while (current != nullptr)
    {
        cout << current -> data << endl;
        current = current -> next;
    }
    cout << "\nDown of stack\n----------------\n";
}

void DynamicList::printSize() {
    cout << "\nSize of stack: " << currentSize << endl;
}

bool DynamicList::isEmpty() {
    if (pHead -> next == nullptr) return true;
    else return false;
}

bool DynamicList::addAfter(int new_item, int paste_after) {
    Node* pCurrent = pHead -> next;
    while ((pCurrent != nullptr) && (pCurrent->data)!=paste_after) {
        pCurrent = pCurrent->next;
    }
    if (pCurrent == nullptr){
        return false;
    } else {
        Node *pTemp = new Node();
        pTemp->data = new_item;
        pTemp->next = pCurrent->next;
        pCurrent->next = pTemp;
        if (pTemp->next == nullptr){
            last = pTemp;
        }
        currentSize++;
        return true;
    }
}

bool DynamicList::addBefore(int new_item, int paste_before) {
    Node* pPrev = pHead; 
    Node* pCurrent = pHead -> next;

    while ((pCurrent != nullptr) && (pCurrent->data) != paste_before) {
        pPrev = pCurrent;
        pCurrent = pCurrent->next;
    }

    if (pCurrent == nullptr){
        return false;
    } else {
        Node *pTemp = new Node();
        pTemp->data = new_item;
        pTemp->next = pCurrent;
        pPrev->next = pTemp;
        currentSize++;
        return true;
    }
}

