#include "DynamicStack.h"
#include <iostream>
using namespace std;


DynamicStack::DynamicStack(/* args */) {
    
}


DynamicStack::~DynamicStack() {

}

void DynamicStack::addNumber(int new_number) {
    Node* pTemp = new Node();
    cout << "Enter new number\n";
    pTemp -> data = new_number;
    pTemp -> next = this -> sp;
    this -> sp = pTemp;
    this -> size++;
}

void DynamicStack::showAll() {
    Node *current = sp;
    cout << "\n----------------\nUp of stack\n\n";
    while (current != nullptr)
    {
        cout << current -> data << endl;
        current = current -> next;
    }
    cout << "\nDown of stack\n----------------\n";
}

void DynamicStack::removeTop() {
    Node* pTemp = sp;
    sp = sp -> next;    
    delete pTemp;
}

void DynamicStack::printSize() {
    
}

bool DynamicStack::isEmpty() {
    if (sp == nullptr) return true;
    else return false;
}
