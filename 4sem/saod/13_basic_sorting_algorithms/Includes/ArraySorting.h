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
    
    
public:
    ArraySorting();
    void print_array(int[], int);
    void bubble_sorting(int[], int);
    void insertion_sorting(int[], int);
    void sorting_by_choice(int[], int);
};

