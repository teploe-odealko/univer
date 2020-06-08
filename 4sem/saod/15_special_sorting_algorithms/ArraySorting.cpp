#include "ArraySorting.h"
#include "stdlib.h"
#include <iostream>
#include "DynamicList.h"
#include <math.h>
using namespace std;

ArraySorting::ArraySorting(){}



void swap (int *a, int *b)  
{  
    int temp = *a;  
    *a = *b;  
    *b = temp;  
} 

void randomize (int arr[], int n)  
{  

    srand (time(NULL));   
    for (int i = n - 1; i > 0; i--)  
    {  
        int j = rand() % (i + 1);  
        swap(&arr[i], &arr[j]);  
    }  
}  

void ArraySorting::generate_array_for_pocket_sorting(int arr[], int len)
{
    for (int i = 0; i < len; i++)
        arr[i] = i;
            
    randomize(arr, len);
    
}

void ArraySorting::print_array(int arr[], int len)
{
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
}



void my_swap(int& a, int& b)
{
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

void ArraySorting::pocket_sorting_suppurted_array(int arr[], int supported_arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        supported_arr[arr[i]] = arr[i];
    }
}

void ArraySorting::pocket_sorting(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        while (arr[i] != i)
        {
            my_swap(arr[i], arr[arr[i]]);
        }
    }
}

void ArraySorting::pocket_sorting_same_keys(int arr[], int len, int num_of_keys)
{
    DynamicList keys_list[num_of_keys];
    for (int i = 0; i < len; i++)
    {
        keys_list[arr[i]].pushBack(arr[i]);
    }

    int j = 0;
    for (int i = 0; i < num_of_keys; i++)
    {
        if (keys_list[i].pHead->next != nullptr)
        {
            Node* pCurrent = keys_list[i].pHead->next;
            while (pCurrent != nullptr)
            {
                arr[j] = pCurrent->data;
                pCurrent = pCurrent->next;
                j++;
            }
        }
    }
}

int get_k_digit(int num, int k)
{
    return (num / (int)pow(10, k-1)) % 10;
}

void ArraySorting::k_bit_sorting(int arr[], int len, int k)
{
    
    for (int l = 1; l <= k; l++)
    {
        DynamicList keys_list[10];
        for (int i = 0; i < len; i++)
        {
            keys_list[get_k_digit(arr[i], l)].pushBack(arr[i]);
        }

        int j = 0;
        for (int i = 0; i < 10; i++)
        {
            Node* pCurrent = keys_list[i].pHead->next;
            while (pCurrent != nullptr)
            {
                arr[j] = pCurrent->data;
                pCurrent = pCurrent->next;
                j++;
            }
        }
    }
}

