#include "ArraySorting.h"
#include "stdlib.h"
#include <iostream>
#include <math.h>
using namespace std;

ArraySorting::ArraySorting(){}

void ArraySorting::print_array(int arr[], int len)
{
    // cout << endl;
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl ;
    cout << "Перестановок - " << swaps << endl 
         << "Сравнений    - " << comparisons << endl;
    
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

void ArraySorting::shell_sort(int arr[], int len)
{
    swaps = 0, comparisons = 0;
    int n_step = log2(len) - 1;
    int steps[n_step];
    int k;
    for (k = n_step - 1; k >= 0; k--)
    {
        cout << k << endl;
        steps[n_step-1-k] = pow(2, k+1) - 1;
    }
    // print_array(steps, n_step);
    int step, temp, j, i;
    for (int m = 0; m < n_step; m++)
    {
        step = steps[m];
        for (i = step; i < len; i++)
        {
            temp = arr[i];
            j = i - step;
            while (j >= 0 && temp < arr[j])
            {
                arr[j+step] = arr[j];
                j = j - step;
                swaps++;
                comparisons++;
            }
            if (j >= 0)
                comparisons++;
            arr[j+step] = temp;
        }
    }
}

void ArraySorting::quick_sort(int arr[], int left, int right)
{
    int i, j, temp, sred;
    i = left;
    j = right;
    sred = arr[(left + right) / 2];
    do
    {
        while (arr[i] < sred)
            i++;
        while (arr[j] > sred)
            j--;
        if (i <= j)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
        
    } while (i < j);
    if (left < j)
        quick_sort(arr, left, j);
    if (i < right)
        quick_sort(arr, i, right);
}