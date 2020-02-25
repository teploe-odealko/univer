#include "DynamicList.h"
#include <iostream>
using namespace std;

template <typename T>
DynamicList<T>::DynamicList() {
    pHead = new Node<T>();
    pHead->next = nullptr;
    last = pHead;
}

template <typename T>

DynamicList<T>::~DynamicList() {
    
}

template <typename T>
void DynamicList<T>::pushBack(T new_item) {
    Node<T>* pTemp = new Node<T>();
    pTemp->data =  new_item;
    pTemp->next = nullptr;
    last->next = pTemp;
    last = pTemp;
    currentSize++;
}

template <typename T>
void DynamicList<T>::showAll() {
    Node<T>* current = pHead -> next;
    cout << "\n----------------\nFIRST\n\n";

    while (current != nullptr)
    {
        cout << current->data << endl;
        current = current -> next;
        
    }

    cout << "\nLAST\n----------------\n";
}

template <typename T>
bool DynamicList<T>::removeItem(int index) {
    Node<T>* pPrev = pHead; 
    Node<T>* pCurrent = pHead -> next;
    if (index < currentSize){
        for (int i = 0; i < index; i++){
            pPrev->next = pCurrent->next;
        }
        if (pPrev->next == nullptr){
            last = pPrev;
        }
        currentSize--;
        return true;

    } else {
        return false;
    }
}


template <typename T>
void DynamicList<T>::printSize() {
    cout << "\nSize of stack: " << currentSize << endl;
}


template <typename T>
bool DynamicList<T>::isEmpty() {
    if (pHead -> next == nullptr) return true;
    else return false;
    
}


template <typename T>
T* DynamicList<T>::getItemByIndex(int index){
    Node<T> *pCurrent = pHead;
    for (int i = 0; i < index; i++){
        pCurrent = pCurrent->next;
    }
    return &(pCurrent -> data);
}