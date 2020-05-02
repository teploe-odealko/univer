#include <iostream>
#include <algorithm>
#include <math.h>
#include "ArraySorting.h"

using namespace std;

int generate_int()
{
    return rand() % 100 + 1;
}

int main(){
    // int n_vertices;
    ArraySorting sorting;
    int choice = 1;    
    int len;
    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) pocket sorting with support array\n"
        "2) pocket sorting without support array\n"
        "3) sort an array of size 1000\n"
        "4) sort an array of size 10000\n"
        "Выбрать: ";
        cin >> choice;
        if (choice > 4)
            continue;

        len = 10;
        int arr[len] = {1, 8, 5, 2, 6, 0, 3, 9, 4, 7};
        int arr_same_keys[30] = {1, 8, 5, 2, 6, 0, 3, 9, 4, 7, 1, 8, 5, 2, 6, 0, 3, 9, 4, 7, 1, 8, 5, 2, 6, 0, 3, 9, 4, 7};
        int arr_k_bit[15] = {56, 17, 83, 9, 11, 27, 33, 02, 16, 45, 8, 37, 66, 99, 90};
        int arr_copy[len];
        // for (int i = 0; i < len; i++)
            // arr[i] = generate_int();
        cout << "original array: \n";
        for (auto const& val: arr)
            cout << val << " ";
        cout << endl;

        // copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        // sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.pocket_sorting_suppurted_array(arr, arr_copy, len);
        cout << "\npocket sorting with support array: \n";
        sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        // sorting.zero_values();
        sorting.pocket_sorting(arr_copy, len);
        cout << "\npocket sorting: \n";
        sorting.print_array(arr_copy, len);

        // copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.pocket_sorting_same_keys(arr_same_keys, 30, 10);
        cout << "\npocket_sorting_same_keys: \n";
        sorting.print_array(arr_same_keys, 30);

        
        sorting.k_bit_sorting(arr_k_bit, 15, 2);
        cout << "\npocket_sorting_same_keys: \n";
        sorting.print_array(arr_k_bit, 15);

    }
    return 0;
}