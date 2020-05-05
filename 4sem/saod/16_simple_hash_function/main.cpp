#include <iostream>
#include <algorithm>
#include <math.h>
#include "HashTable.h"
#include <string>

using namespace std;

int generate_int()
{
    return rand() % 100 + 1;
}

int main(){
    // int n_vertices;
    HashTable hash_table;
    int choice = 1; 
    int res;

    hash_table.print();
    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) Find a string\n"
        "Select: ";
        cin >> choice;
        if (choice > 1)
            continue;
        if (choice == 1)
        {
            string str_to_find;
            cout << "Put your string: ";
            cin >> str_to_find;
            res = hash_table.find(str_to_find);
            if (res < 0)
                cout << "No such key\n";
            else 
                cout << "Element " << str_to_find << " has index " << res << endl; 
        }
    }


    return 0;
}