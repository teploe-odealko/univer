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

struct HashTable
{
private:
    // int n_vertices;
    
    // void add_TreeNodes(TreeNode**, int);
    int swaps;
    int comparisons;
    void sito(int arr[], int len, int i);
    string hash_table[10];
    string key_words[10] = {"endl", "int", "return",
    "string", "void", "catch", "progma", "for", "bool", "include"};
    
    
public:
    HashTable();
    int hash_func(string);
    void zero_values();
    void print_array(int[], int);
    void print();
    int find(string);
    // void pocket_sorting(int[], int);
    
};