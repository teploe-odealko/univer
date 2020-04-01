#include <iostream>
#include "LinkedList.h"
#include "DynamicList.h"
#include <limits>

using namespace std;

int main(){
    int choice = 1;
    LinkedList<LinkedList<int>> generalList;
    

    while (choice != 0)
    {
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) Add new SUB_list to GENERAL_List\n"
        "2) Add new item to some SUB_list\n"
        "3) Find item\n"
        "4) Show all items\n"
        "5) Remove SUB_list from GENERAL_list\n"
     //   "6) Remove item from SUB_list\n"
        "Select: ";
        cin >> choice;
        cout << endl;
        bool res;
        switch (choice){
        case 1:
        {
            int list_id;
            int paste_after;
            cout << "Enter SUB List ID: ";
            cin >> list_id;
            LinkedList<int> subList = LinkedList<int>(list_id);
            if (generalList.isEmpty())
            {
                generalList.pushBack(subList);
            }
            else
            {
                cout << "\nSUB List ID AFTER which you want to insert a new SUB List: ";
                cin >> paste_after;
                res = generalList.addAfter(subList, paste_after);
                if (res)
                    cout << "SUCESS!!!\n";
                else
                    cout << "FAIL!!!\n";
            }
            break;
        }
        case 2:
            if (generalList.isEmpty())
            {
                cout << "GENERAL_list is Empty. Add SUB_list to GENERAL_list (1)\n";
            }
            else
            {
                int subListId, new_number, paste_after;
                res = false;

                cout << "\nEnter SUB List ID: "; 
                cin >> subListId;
                cout << "\nEnter new number to add into SUB_list: "; 
                cin >> new_number;
                NodeLL<LinkedList<int>> *pSubListNode = generalList.findSubList(subListId);

                if (pSubListNode != generalList.pHead)
                {
                    LinkedList<int> pSubList = pSubListNode->data;
                    if (pSubList.isEmpty())
                    {
                        pSubList.pushBack(new_number);
                    }
                    else
                    {
                        cout << "\nEnter the item AFTER which you want to insert a new item: ";
                        cin >> paste_after;
                        res = pSubList.addAfter(new_number, paste_after);
                    }
                }
                if (res) cout << "Successful!\n";
                // else cout << "Item \"" << paste_after << "\" not found. Item was not added to List\n";
            }
            break;

        // case 3:
        //     if (!generalList.isEmpty()){

        //     }
        //     break;
            
        case 4:
            if (generalList.isEmpty())
            {
                cout << "GENERAL_list is Empty. Add SUB_list to GENERAL_list (1)\n";
            }
            else
            {
                generalList.showAllDirect();
                cout << endl;
            }

            break;

        // case 5:

        //     if (!generalList.isEmpty()){
        //         int subListIndex = selectSubList(generalList.getSize());
        //         LinkedList<int> *pSubList;
        //         pSubList = generalList.getItemByIndex(subListIndex);
        //         pSubList -> removeAll();
        //         generalList.removeItem(subListIndex);

        //         cout << "Successful!\n";



        //     } else {
        //         cout << "\nArray List is empty. Nothing to remove.\n";
        //     }

        //     break;

        // case 6:

        //     if (!generalList.isEmpty()){
        //         int subListIndex = selectSubList(generalList.getSize());

        //         bool result = myLinkedList.removeItem(item_to_delete);
        //         if (result) cout << "Successful!\n";
        //         else cout << "Item not found\n";


        //     } else {
        //         cout << "\nArray List is empty. Nothing to remove.\n";
        //     }
        //     break;

        default:
    
            break;
        }
    }
    return 0;
}