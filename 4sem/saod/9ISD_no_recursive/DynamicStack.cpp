#include "DynamicStack.h"
#include <iostream>
using namespace std;



DynamicStack::DynamicStack(/* args */) {
    
}


DynamicStack::~DynamicStack() {

}

void DynamicStack::addItem(TreeNode *treeNode, int level) {
    StackNode* pTemp = new StackNode();
    pTemp->level = level;
    pTemp -> treeNode = treeNode;
    pTemp -> next = this -> sp;
    this -> sp = pTemp;
    this -> size++;
}

void DynamicStack::showAll() {
    StackNode *current = sp;
    cout << "\n----------------\nUp of stack\n\n";
    while (current != nullptr)
    {
        cout << current -> treeNode -> data << endl;
        current = current -> next;
    }
    cout << "\nDown of stack\n----------------\n";
}

void DynamicStack::removeTop() {
    StackNode* pTemp = sp;
    sp = sp -> next;    
    delete pTemp;
    this -> size--;
}

StackNode* DynamicStack::getTopPtr(){
    StackNode* pTemp = sp;
    return pTemp;
}

void DynamicStack::addStackNode(StackNode* new_Stacknode){
    new_Stacknode -> next = this -> sp;
    this -> sp = new_Stacknode;
    this -> size++;
}




bool DynamicStack::isEmpty() {
    if (sp == nullptr) return true;
    else return false;
}
