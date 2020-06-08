#include <iostream>
#include <algorithm>
#include <math.h>
#include "ArraySorting.h"

using namespace std;

int generate_int()
{
    return rand() % 100;
}

int main(){
    // int n_vertices;
    ArraySorting sorting;
    int choice = 1;    
    int len;
    // while (choice != 0){
        // cout << "\nSelect action:\n"
        // "0) Exit\n"
        // "1) pocket sorting with support array\n"
        // "2) pocket sorting without support array\n"
        // "3) sort an array of size 1000\n"
        // "4) sort an array of size 10000\n"
        // "Select: ";
        // cin >> choice;
        // if (choice > 4)
        //     continue;

    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) sort an array of size 10\n"
        "2) sort an array of size 100\n"
        "3) sort an array of size 1000\n"
        "4) sort an array of size 10000\n"
        "Select: ";
        cin >> choice;
        if (choice > 4)
            continue;

        len = pow(10, choice);
        int arr_pocket[len];
        int arr_pocket_support[len];
        int arr_pocket_copy[len];
        int arr_pocket_same_keys[len];
        int arr_k_bit[len];

        sorting.generate_array_for_pocket_sorting(arr_pocket, len);
        copy(&(arr_pocket[0]), &(arr_pocket[len]), &(arr_pocket_copy[0]));
        // int arr[len] = {1, 8, 5, 2, 6, 0, 3, 9, 4, 7};
        // int arr_same_keys[30] = {1, 8, 5, 2, 6, 0, 3, 9, 4, 7, 1, 8, 5, 2, 6, 0, 3, 9, 4, 7, 1, 8, 5, 2, 6, 0, 3, 9, 4, 7};
        // int arr_k_bit[15] = {56, 17, 83, 9, 11, 27, 33, 02, 16, 45, 8, 37, 66, 99, 90};
        // int arr_copy[len];
        // for (int i = 0; i < len; i++)
            // arr[i] = generate_int();аем Вас 05.06.2020г. 
        
        // for (auto const& val: arr)
        //     cout << val << " ";
        // cout << endl;

        cout << "original array: \n";
        sorting.print_array(arr_pocket_copy, len);

        // copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.pocket_sorting_suppurted_array(arr_pocket_copy, arr_pocket_support, len);
        cout << "\npocket sorting with support array: \n";
        sorting.print_array(arr_pocket_support, len);

        copy(&(arr_pocket[0]), &(arr_pocket[len]), &(arr_pocket_copy[0]));
        sorting.pocket_sorting(arr_pocket_copy, len);
        cout << "\npocket sorting: \n";
        sorting.print_array(arr_pocket_copy, len);


        cout << "\n\noriginal array for pocket sorting with same keys: \n";
        for (int i = 0; i < len; i++)
            arr_pocket_same_keys[i] = generate_int();
        sorting.print_array(arr_pocket_same_keys, len);
        sorting.pocket_sorting_same_keys(arr_pocket_same_keys, len, 100);
        cout << "\npocket_sorting_same_keys: \n";
        sorting.print_array(arr_pocket_same_keys, len);

        

    cout << "\n\noriginal array for k_bit sorting: \n";
        for (int i = 0; i < len; i++)
            arr_k_bit[i] = generate_int();
        sorting.print_array(arr_k_bit, len);
        sorting.k_bit_sorting(arr_k_bit, len, 2);
        cout << "\nk_bit_sorting: \n";
        sorting.print_array(arr_k_bit, len);
        cout << "\n";
    }
    return 0;
    
}