#include <iostream>
#include <algorithm>
#include <math.h>
#include "HashTable.h"
#include <string>

using namespace std;

int main(){
    // int n_vertices;
    
    int choice = 1; 
    int res;
    int m;
    cout << "Put Hash table size (m): ";
    cin >> m;
    string key;

    HashTable hash_table(m);
    // hash_table.print();
    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) add key word\n"
        "2) Find a string\n"
        "3) print hash table\n"
        "4) delete key_word\n"
        "5) load the prepared list of 20 keywords\n"
        "Select: ";
        cin >> choice;
        if (choice > 5)
            continue;
        
        switch (choice)
        {
        case 1:
            cout << "\nPut new key word: ";
            cin >> key;
            hash_table.add_key(key);
            
            break;
        case 2:
        {
            string str_to_find;
            cout << "\nPut your string: ";
            cin >> str_to_find;
            res = hash_table.find(str_to_find);
            if (res < 0)
                cout    << "Fail! No such key\n"
                        << "Comparisons = " 
                        << hash_table.comparisons
                        << endl;
            else 
                cout    << "Sucsess! Element was found\n"
                        << "Comparisons = " 
                        << hash_table.comparisons
                        << endl; 
        
            break;
        }

        case 3:
            hash_table.print();
            break;

        case 4:
        {
            string str_to_remove;
            cout << "\nPut string you want to remove: ";
            cin >> str_to_remove;
            res = hash_table.remove(str_to_remove);
            if (res < 0)
                cout    << "Fail! No such key\n"
                        << "Comparisons = " 
                        << hash_table.comparisons
                        << endl;
            else 
                cout    << "Sucsess! Element was removed\n"
                        << "Comparisons = " 
                        << hash_table.comparisons
                        << endl; 
        
            break;
        }

        case 5:
            hash_table.add_prepared_list();
            break;

        default:
            break;
        }

        
        
    }


    return 0;
}