#include "GeneralList.h"
#include <iostream>

using namespace std;

GeneralList::GeneralList()
{
    pHead = new NodeLL();
    pHead->right = pHead;
    pHead->left = pHead;
}

GeneralList::~GeneralList() {
    
}
 
void GeneralList::pushBack(SubList* new_item)
{
    NodeLL* pTemp = new NodeLL();
    pTemp->data = new_item;
    pTemp->left = pHead;
    pTemp->right = pHead;
    pHead->right = pTemp;
    pHead->left = pTemp;
    currentSize++;
}

void GeneralList::showAllDirect() 
{
    NodeLL *current_list = pHead -> right;
    NodeNum *num;
    cout << "----------------\nFIRST LIST\n\n";
    while (current_list != pHead)
    {
        cout << "List " << current_list->data->id << ": ";
        num = current_list->data->pHead->right;
        while (num != current_list->data->pHead)
        {
            cout << num->data << " ";
            num = num->right;
        }
        cout << endl;
        current_list = current_list->right;
    }
    cout << "\nLAST LIST\n----------------\n";
}


bool GeneralList::removeItem(int item_to_remove) {
    NodeLL* pCurrent = pHead->right;

    while ((pCurrent != pHead) && (pCurrent->data)->id != item_to_remove) {
        pCurrent = pCurrent->right;
    }
    if (pCurrent == pHead){ // Если заданного элемента нет в списке
        return false;
    } else {  
        pCurrent->left->right = pCurrent->right;
        pCurrent->right->left = pCurrent->left;
        pCurrent->data->~SubList();
        delete pCurrent;
        currentSize--;
        return true;
    }
}


bool GeneralList::isEmpty() 
{
    if (pHead -> right == pHead) return true;
    else return false;
}

int GeneralList::getSize() 
{
    return currentSize;
}

bool GeneralList::addAfter(SubList *new_item, int paste_after) 
{
    NodeLL* pCurrent = findSubList(paste_after);
    if (pCurrent == NULL)
    {
       return false;
    }
    else 
    {
        NodeLL *pTemp = new NodeLL();

        pTemp->data = new_item;
        pTemp->right = pCurrent->right;
        pTemp->left = pCurrent;
        pCurrent->right->left = pTemp;
        pCurrent->right = pTemp;
        currentSize++;
    }
    return true;
}

bool GeneralList::addBefore(SubList *new_item, int paste_before) {
    NodeLL* pCurrent = findSubList(paste_before);
    if (pCurrent == NULL)
        return false;
    else 
    {
        NodeLL* pTemp = new NodeLL();

        pTemp->data = new_item;
        pTemp->right = pCurrent;
        pTemp->left = pCurrent->left;
        pCurrent->left->right = pTemp;
        pCurrent->left = pTemp;
        currentSize++;
        return true;
    }
}

NodeLL *GeneralList::findSubList(int searchBy)
{
    NodeLL *pCurrent = pHead->right;
    while ((pCurrent != pHead) && (pCurrent->data)->id != searchBy)
    {
        pCurrent = pCurrent->right;
    }
    if (pCurrent == pHead)
        pCurrent = NULL;
    return pCurrent;
}