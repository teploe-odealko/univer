#include <iostream>
#include "LinkedList.h"
#include "DynamicList.h"
#include <limits>

using namespace std;



int main(){
    int choice = 1;
    DynamicList<LinkedList<int>> generalList;
    

    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) Add new SUB_list to GENERAL_List\n"
        "2) Add new item to some SUB_list\n"
        "3) Find item\n"
        "4) Show all items\n"
        "5) Remove SUB_list from GENERAL_list\n"
        "6) Remove item from SUB_list\n"
        "Select: ";
        cin >> choice;
        cout << endl;
        switch (choice){

        case 1:
            {
            LinkedList<int> subList;
            generalList.pushBack(subList);
            break;
            }
            
        case 2:

            if (!generalList.isEmpty()){   // Проверка на пустоту главного списка
                int subListIndex, new_number, paste_after;
            
                cout << "\n\nAvailable SUB_lists\n-------------------\n";  // Вывод доступных списков 
                for (int i = 0; i < generalList.getSize(); i++){
                    cout << i << " ";
                }
                cout << "\n-------------------\nSelect: ";

                cin >> subListIndex;
                while (subListIndex > generalList.getSize()){  // Проверка на корректный выбор списка
                    cout << "\nIndex does not exist\nSelect again: ";
                    cin >> subListIndex;
                }

                cout << "\nEnter new number to add into SUB_list: "; 
                cin >> new_number;
                LinkedList<int> *pSubList = generalList.getItemByIndex(subListIndex);

                bool result = true;
                if (pSubList -> isEmpty()){
                    pSubList -> pushBack(new_number);
                } else {
                    cout << "\nEnter the item AFTER which you want to insert a new item: ";
                    cin >> paste_after;
                    result = pSubList -> addBefore(new_number, paste_after);
                }
                
                if (result) cout << "Successful!\n";
                else cout << "Item \"" << paste_after << "\" not found. Item was not added to List\n";
            } else {
                cout << "GENERAL_list is Empty. Add SUB_list to GENERAL_list (1)\n";
            }

            break;

        // case 3:
        //     myLinkedList.showAllDirect();
        //     break;
            
        case 4:
            if (!generalList.isEmpty()){
                LinkedList<int> *pSubList;
                for (int i = 0; i < generalList.getSize(); i++){
                    pSubList = generalList.getItemByIndex(i);
                    cout << endl << i << "|\n";
                    pSubList -> showAllDirect();
                    cout << endl;
                }
            } else {
                cout << "GENERAL_list is Empty. Add SUB_list to GENERAL_list (1)\n";
            }

            break;

        // case 5:

        //     if (!myLinkedList.isEmpty()){
        //         int item_to_delete;
        //         cout << "\nEnter the the item you want to delete: ";
        //         cin >> item_to_delete;
        //         bool result = myLinkedList.removeItem(item_to_delete);
        //         if (result) cout << "Successful!\n";
        //         else cout << "Item not found\n";


        //     } else {
        //         cout << "\nArray List is empty. Nothing to remove.\n";
        //     }

        //     break;

        // case 6:
        //     myLinkedList.printSize(); 
        //     break;

        // default:
    
        //     break;
        // }
        
    
        }
    }
    return 0;

}