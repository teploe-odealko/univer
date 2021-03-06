#pragma once
#define Tree_h

// struct TreeNode
// {
//     TreeNode* right;
//     TreeNode* left;
//     int data;
//     int counter = 0;
    
// };q

struct ArraySorting
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
    void bubble_sorting(int[], int);
    void insertion_sorting(int[], int);
    void sorting_by_choice(int[], int);
    void shell_sort(int[], int);
    void quick_sort(int[], int, int);
    void pyramid_sorting(int[], int);
};