#include "SubList.h"
#include <iostream>

using namespace std;

SubList::SubList(int new_id) {
	pHead = new NodeNum();
	pHead->right = pHead;
	pHead->left = pHead;
	id = new_id;
}

SubList::SubList() {
	pHead = new NodeNum();
	pHead->right = pHead;
	pHead->left = pHead;
}

SubList::~SubList() {
	NodeNum* pCurrent = pHead->right;
	NodeNum* to_delete;

	while(pCurrent != pHead)
	{
		to_delete = pCurrent;
		pCurrent = pCurrent->right;
		delete to_delete;
	}
	delete pHead;
}
 
void SubList::pushBack(int new_item)
{
	NodeNum* pTemp = new NodeNum();
	pTemp->data =  new_item;
	pTemp->left = pHead;
	pTemp->right = pHead;
	pHead->right = pTemp;
	pHead->left = pTemp;
	currentSize++;
}

bool SubList::removeItem(int item_to_remove) {
    NodeNum *pCurrent = pHead -> right;

    while ((pCurrent != pHead) && (pCurrent->data)!=item_to_remove) 
	{
        pCurrent = pCurrent->right;
    }
    if (pCurrent == pHead)
        return false;
	else
	{
        pCurrent->left->right = pCurrent->right;
        pCurrent->right->left = pCurrent->left;
        delete pCurrent;
        currentSize--;
        return true;
    }
}

bool SubList::isEmpty() {
	if (pHead -> right == pHead) return true;
	else return false;
}

int SubList::getSize() {
	return currentSize;
}

bool SubList::addAfter(int new_item, int paste_after) 
{
	NodeNum* pCurrent = findDirect(paste_after);
	if (pCurrent == pHead)
	{
	   return false;
	} 
	else 
	{
		NodeNum *pTemp = new NodeNum();
		pTemp->data = new_item;

		pTemp->right = pCurrent->right;
		pTemp->left = pCurrent;
		pCurrent->right->left = pTemp;
		pCurrent->right = pTemp;


		currentSize++;
	}
	return true;
}

bool SubList::addBefore(int new_item, int paste_before) {
    NodeNum* pCurrent = findDirect(paste_before);
    if (pCurrent == pHead){
        return false;
    } else {
        NodeNum* pTemp = new NodeNum();
        pTemp->data = new_item;

        pTemp->right = pCurrent;
        pTemp->left = pCurrent->left;
        pCurrent->left->right = pTemp;
        pCurrent->left = pTemp;

		
        currentSize++;
        return true;
    }
}

NodeNum *SubList::findDirect(int searchBy)
{
	NodeNum *pCurrent = pHead->right;
	while ((pCurrent != pHead) && (pCurrent->data) != searchBy)
	{
		pCurrent = pCurrent->right;
	}
	return pCurrent;
}