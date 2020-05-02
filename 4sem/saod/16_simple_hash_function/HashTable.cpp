#include "HashTable.h"
#include "stdlib.h"
#include <iostream>
#include "DynamicList.h"
#include <math.h>
#include <string>
using namespace std;

HashTable::HashTable()
{
    for (int i = 0; i < 10; i++)
    {
        hash_table[hash_func(key_words[i])] = key_words[i];
    }
}


int HashTable::hash_func(string key)
{
    int sum = 0;
    for (int i = 0; i < (int)key.length(); i++)
    {
        sum += key[i];
    }
    return sum % 10;
}

void HashTable::print()
{
    cout    << "\nHashTable\n" 
            << "-------------------\n";
    for (int i = 0; i < 10; i++)
    {
        cout << i << " - " << hash_table[i] << endl;
    }
    cout << "-------------------\n";
}

int HashTable::find(string to_find)
{
    string key = hash_table[hash_func(to_find)];
    return (key == to_find) ? hash_func(to_find) : -1;
}

