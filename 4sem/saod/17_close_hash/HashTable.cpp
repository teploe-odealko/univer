#include "HashTable.h"
#include "stdlib.h"
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

HashTable::HashTable(int set_m)
{
    m = set_m;
    hash_table = new string[m] {""};
}


int HashTable::hash_func(string key)
{   
    int sum = 0;
    for (int i = 0; i < (int)key.length(); i++)
    {
        sum += (int)key[i];
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
        cout << hash_table[i];
        cout << endl;
    }
    cout << "-------------------\n";
}

int HashTable::add_key(string new_key)
{
    comparisons = 0;
    int index, i;
    for (i = 0; i < m; i++) 
    {
        index = ((hash_func(new_key) + i) % m); 

        comparisons++;
        if (hash_table[index] == new_key)
            return 0;

        comparisons++;
        if (hash_table[index] == "")
            break;        
    }

    if (i == m)
        return -1;
    hash_table[index] = new_key;
    return 1;
}

int HashTable::find(string to_find)
{
    comparisons = 0;
    int index, i;
    for (i = 0; i < m; i++)
    {
        index = ((hash_func(to_find) + i) % m); 
        if (hash_table[index] == to_find)
            break;
        comparisons++;
    }
    comparisons++;
    if (i == m)
        return -1;
    return 1;
}



void HashTable::add_prepared_list()
{
    for (int i = 0; i < 20; i++)
    {
        add_key(key_words[i]);
    }
}