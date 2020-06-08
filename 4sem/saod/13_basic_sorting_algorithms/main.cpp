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
        "1) Sorting an array by size 10\n"
        "2) Sorting an array by size 100\n"
        "3) Sorting an array by size 1000\n"
        "4) Sorting an array by size 10000\n"
        "Select: ";
        cin >> choice;
        if (choice > 4)
            continue;

        len = pow(10, choice);
        int arr[len];
        int arr_copy[len];
        for (int i = 0; i < len; i++)
            arr[i] = generate_int();
        cout << "Original array: \n";
        for (auto const& val: arr)
            cout << val << " ";
        cout << endl;

        // copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        // sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.bubble_sorting(arr_copy, len);
        cout << "\nBubble sort: \n";
        sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.insertion_sorting(arr_copy, len);
        cout << "\nthe insertion sort: \n";
        sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.sorting_by_choice(arr_copy, len);
        cout << "\nsorting by Choice: \n";
        sorting.print_array(arr_copy, len);

    }
    return 0;
}