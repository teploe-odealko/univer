#pragma once
#define Tree_h

// struct TreeNode
// {
//     TreeNode* right;
//     TreeNode* left;
//     int data;
//     int counter = 0;
    
// };q

class ArraySorting
{
private:
    // int n_vertices;
    
    // void add_TreeNodes(TreeNode**, int);
    int swaps;
    int comparisons;
    void sito(int arr[], int len, int i);
    
    
public:
    ArraySorting();
    void zero_values();
    void print_array(int[], int);
    void pocket_sorting_suppurted_array(int[], int[], int);
    void pocket_sorting(int[], int);
    void pocket_sorting_same_keys(int[], int, int);
    void k_bit_sorting(int[], int, int);
};