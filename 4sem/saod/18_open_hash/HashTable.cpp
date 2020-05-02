#include "HashTable.h"
#include "stdlib.h"
#include <iostream>
#include "DynamicList.h"
#include <math.h>
#include <string>
using namespace std;

HashTable::HashTable(int set_m)
{
    m = set_m;
    hash_table = new DynamicList[m];
}


int HashTable::hash_func(string key)
{   
    int sum = 0;
    for (int i = 0; i < (int)key.length(); i++)
    {
        sum += (int)key[i];
        // cout << sum << endl;
    }
    return sum % m;
}

void HashTable::print()
{
    cout    << "\nHashTable\n" 
            << "-------------------\n";
    for (int i = 0; i < m; i++)
    {
        cout << i << " - ";
        Node* pCurrent = hash_table[i].pHead->next;
        while (pCurrent != nullptr)
        {
            cout << pCurrent->data << " ";
            pCurrent = pCurrent->next;
        }
        cout << endl;
    }
    cout << "-------------------\n";
}

void HashTable::add_key(string new_key)
{

    int index = hash_func(new_key);
    Node* pCurrent= hash_table[index].pHead;
    while (pCurrent != nullptr && pCurrent->data != new_key)
    {
        pCurrent = pCurrent->next;
        comparisons++;
    }
    comparisons++;
    if (pCurrent == nullptr)
        hash_table[index].pushBack(new_key);
}

int HashTable::find(string to_find)
{
    comparisons = 0;
    int index = hash_func(to_find);
    Node* pCurrent= hash_table[index].pHead;

    while (pCurrent != nullptr && pCurrent->data != to_find)
    {
        pCurrent = pCurrent->next;
        comparisons++;
    }
    comparisons++;
    if (pCurrent == nullptr)
        return -1;
    return 1;
}


int HashTable::remove(string to_remove)
{
    comparisons = 0;
    int index = hash_func(to_remove);
    Node *pPrev;
    Node *pCurrent= hash_table[index].pHead;

    while (pCurrent != nullptr && pCurrent->data != to_remove)
    {
        pPrev = pCurrent;
        pCurrent = pCurrent->next;
        comparisons++;
    }
    comparisons++;
    if (pCurrent == nullptr)
        return -1;

    pPrev->next = pCurrent->next;
    delete pCurrent;
    return 1;
}

void HashTable::add_prepared_list()
{
    for (int i = 0; i < 20; i++)
    {
        add_key(key_words[i]);
    }
}