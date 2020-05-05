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
        "1) sort an array of size 10\n"
        "2) sort an array of size 100\n"
        "3) sort an array of size 1000\n"
        "4) sort an array of size 10000\n"
        "Select: ";
        cin >> choice;
        if (choice > 4)
            continue;

        len = pow(10, choice);
        int arr[len];
        int arr_copy[len];
        for (int i = 0; i < len; i++)
            arr[i] = generate_int();
        cout << "original array: \n";
        for (auto const& val: arr)
            cout << val << " ";
        cout << endl;

        // copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        // sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.shell_sort(arr_copy, len);
        cout << "\nShell sorting: \n";
        sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.zero_values();
        sorting.quick_sort(arr_copy, 0, len-1);
        cout << "\nQuick_sorting: \n";
        sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.pyramid_sorting(arr_copy, len);
        cout << "\nPyramid sorting: \n";
        sorting.print_array(arr_copy, len);

    }
    return 0;
}