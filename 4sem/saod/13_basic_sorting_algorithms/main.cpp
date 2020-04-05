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
        "0) Выход\n"
        "1) Сортировка массива размером 10\n"
        "2) Сортировка массива размером 100\n"
        "3) Сортировка массива размером 1000\n"
        "4) Сортировка массива размером 10000\n"
        "Выбрать: ";
        cin >> choice;
        if (choice > 4)
            continue;

        len = pow(10, choice);
        int arr[len];
        int arr_copy[len];
        for (int i = 0; i < len; i++)
            arr[i] = generate_int();
        cout << "Исходный массив: \n";
        for (auto const& val: arr)
            cout << val << " ";
        cout << endl;

        // copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        // sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.bubble_sorting(arr_copy, len);
        cout << "\nПузырьком: \n";
        sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.insertion_sorting(arr_copy, len);
        cout << "\nВставками: \n";
        sorting.print_array(arr_copy, len);

        copy(&(arr[0]), &(arr[len]), &(arr_copy[0]));
        sorting.sorting_by_choice(arr_copy, len);
        cout << "\nВыбором: \n";
        sorting.print_array(arr_copy, len);

    }
    return 0;
}