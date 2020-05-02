#pragma once
#include <string>
#include <iostream>
#define Tree_h
using namespace std;

// #include <stdlib.h>

// struct TreeNode
// {
//     TreeNode* right;
//     TreeNode* left;
//     int data;
//     int counter = 0;
    
// };



class HashTable
{
private:

    int m;
    
    string *hash_table;
    string key_words[20] = {"Vincent", "Vincent", "Hopkins", "Pope", "Vaughan", "Dyer", "Berger", 
    "Stout", "Ware", "Callahan", "Reese", "Shields", "Browning", 
    "Banks", "Shah", "Walters", "Fritz", "Greer", "Cooper", "Cooper"};
    
    
public:
    HashTable(int);
    int hash_func(string);
    int comparisons = 0;
    void print();
    int find(string);
    int add_key(string);
    void add_prepared_list();
};