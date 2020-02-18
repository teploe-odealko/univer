#include "LinkedList.h"
#include <iostream>
using namespace std;

template <typename T> 
LinkedList<T>::LinkedList() {
    pHead = new NodeLL<T>();
    pHead->right = pHead;
    pHead->left = pHead;
}

template <typename T> 
LinkedList<T>::~LinkedList() {
    
}

template <typename T> 
void LinkedList<T>::pushBack(T new_item) {
    NodeLL<T>* pTemp = new NodeLL<T>();
    pTemp->data =  new_item;

    pTemp->left = pHead;
    pTemp->right = pHead;
    pHead->right = pTemp;
    pHead->left = pTemp;
    currentSize++;
}

template <typename T> 
void LinkedList<T>::showAllDirect() {
    NodeLL<T> *current = pHead -> right;
    cout << "----------------\nFIRST ELEMENT\n\n";
    while (current != pHead)
    {
        cout << current->data << endl;
        current = current -> right;
    }
    cout << "\nLAST ELEMENT\n----------------\n";
}

template <typename T> 
void LinkedList<T>::showAllBackward() {
    NodeLL<T> *current = pHead -> left;
    cout << "\n----------------\nLast\n\n";
    while (current != pHead)
    {
        cout << current->data << endl;
        current = current -> left;
    }
    cout << "\nFIRST\n----------------\n";
}

template <typename T> 
bool LinkedList<T>::removeItem(T item_to_remove) {
    NodeLL<T>* pCurrent = pHead -> right;

    while ((pCurrent != pHead) && (pCurrent->data)!=item_to_remove) {
        pCurrent = pCurrent->right;
    }
    if (pCurrent == pHead){ // Если заданного элемента нет в списке
        return false;
    } else {  
        pCurrent->left->right = pCurrent->right;
        pCurrent->right->left = pCurrent->left;
        delete pCurrent;
        currentSize--;
        return true;
    }

}

template <typename T> 
void LinkedList<T>::printSize() {
    cout << "\nSize of stack: " << currentSize << endl;
}

template <typename T> 
bool LinkedList<T>::isEmpty() {
    if (pHead -> right == pHead) return true;
    else return false;
}

template <typename T> 
bool LinkedList<T>::addAfter(T new_item, T paste_after) {
    NodeLL<T>* pCurrent = findDirect(paste_after);
    if (pCurrent == pHead){
        return false;
    } else {
        NodeLL<T> *pTemp = new NodeLL<T>();
        pTemp->data = new_item;

        pTemp->right = pCurrent->right;
        pTemp->left = pCurrent;
        pCurrent->right->left = pTemp;
        pCurrent->right = pTemp;


        currentSize++;
        return true;
    }
}

template <typename T> 
bool LinkedList<T>::addBefore(T new_item, T paste_before) {
    NodeLL<T>* pCurrent = findBackward(paste_before);
    if (pCurrent == pHead){
        return false;
    } else {
        NodeLL<T>* pTemp = new NodeLL<T>();
        pTemp->data = new_item;

        pTemp->right = pCurrent;
        pTemp->left = pCurrent->left;
        pCurrent->left->right = pTemp;
        pCurrent->left = pTemp;

        
        currentSize++;
        return true;
    }
}

