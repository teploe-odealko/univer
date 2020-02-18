#include "LinkedList.h"
#include <iostream>
using namespace std;


LinkedList::LinkedList() {
    pHead = new Node();
    pHead->right = pHead;
    pHead->left = pHead;
}


LinkedList::~LinkedList() {
    
}

void LinkedList::pushBack(int new_item) {
    Node* pTemp = new Node();
    pTemp->data =  new_item;

    pTemp->left = pHead;
    pTemp->right = pHead;
    pHead->right = pTemp;
    pHead->left = pTemp;
    currentSize++;
}

void LinkedList::showAllDirect() {
    Node *current = pHead -> right;
    cout << "\n----------------\nFIRST\n\n";
    while (current != pHead)
    {
        cout << current->data << endl;
        current = current -> right;
    }
    cout << "\nLAST\n----------------\n";
}

void LinkedList::showAllBackward() {
    Node *current = pHead -> left;
    cout << "\n----------------\nLast\n\n";
    while (current != pHead)
    {
        cout << current->data << endl;
        current = current -> left;
    }
    cout << "\nFIRST\n----------------\n";
}

bool LinkedList::removeItem(int item_to_remove) {
    Node* pCurrent = pHead -> right;

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


void LinkedList::printSize() {
    cout << "\nSize of stack: " << currentSize << endl;
}

bool LinkedList::isEmpty() {
    if (pHead -> right == pHead) return true;
    else return false;
}

bool LinkedList::addAfter(int new_item, int paste_after) {
    Node* pCurrent = findDirect(paste_after);
    if (pCurrent == pHead){
        return false;
    } else {
        Node *pTemp = new Node();
        pTemp->data = new_item;

        pTemp->right = pCurrent->right;
        pTemp->left = pCurrent;
        pCurrent->right->left = pTemp;
        pCurrent->right = pTemp;


        currentSize++;
        return true;
    }
}

bool LinkedList::addBefore(int new_item, int paste_before) {
    Node* pCurrent = findBackward(paste_before);
    if (pCurrent == pHead){
        return false;
    } else {
        Node *pTemp = new Node();
        pTemp->data = new_item;

        pTemp->right = pCurrent;
        pTemp->left = pCurrent->left;
        pCurrent->left->right = pTemp;
        pCurrent->left = pTemp;

        
        currentSize++;
        return true;
    }
}

