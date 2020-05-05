#include "ArraySorting.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

ArraySorting::ArraySorting(){}

void ArraySorting::print_array(int arr[], int len)
{
    // cout << endl;
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl ;
    cout << "swaps - " << swaps << endl 
         << "comparisons    - " << comparisons << endl;
    
}

void ArraySorting::bubble_sorting(int arr[], int len)
{
    swaps = 0;
    comparisons = 0;
    int temp;
    for (int i = 1; i < len; i++)
    {
        for (int j = len - 1; j >= i; j--)
        {
            if(arr[j-1] > arr[j])
            {
                temp = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = temp;
                swaps++;
            }
            comparisons++;
        }
    }
}

void ArraySorting::insertion_sorting(int arr[], int len)
{
    swaps = 0, comparisons = 0;
    int temp;
    int j;
    for (int i = 1; i < len; i++)
    {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && temp < arr[j])
        {
            // cout << arr[j] << " " << temp << endl;
            arr[j+1] = arr[j];
            j = j - 1;
            swaps++;
            comparisons++;
            
        }
        // cout << arr[j] << " " << temp << endl;
        if (j >= 0)
            comparisons++;
        arr[j+1] = temp;
    }
}

void ArraySorting::sorting_by_choice(int arr[], int len)
{
    swaps = 0, comparisons = 0;
    int min;
    int k;
    for (int i = 0; i < len-1; i++)
    {
        k = i;
        min = arr[i];
        for (int j = i+1; j < len; j++)
        {
            comparisons++;
            if (min > arr[j])
            {
                k = j;
                min = arr[j];
            }
        }
        swaps++;
        arr[k] = arr[i];
        arr[i] = min;
    }
}
