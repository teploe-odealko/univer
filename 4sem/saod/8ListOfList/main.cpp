#include <iostream>
#include "GeneralList.h"
#include "SubList.h"
// #include "DynamicList.h"

using namespace std;

int main(){
    int choice = 1;
    GeneralList generalList;
    

    while (choice != 0)
    {
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) Add new SUB_list to GENERAL_List\n"
        "2) Add new item to some SUB_list\n"
        "3) Show all\n"
        "4) Remove SUB_list from GENERAL_list\n"
        "5) Remove item from SUB_list\n"
        "Select: ";
        cin >> choice;
        cout << endl;
        bool res;
        switch (choice){
            int SubListId, new_number, find, after_or_before, list_id, item_to_delete;

        case 1:
        {
            cout << "Enter SUB List ID: ";
            cin >> list_id;
            SubList *sublist = new SubList(list_id);
            if (generalList.isEmpty())
            {
                generalList.pushBack(sublist);
            }
            else
            {
                cout << "1) before\n2) after\nSelect: ";
                cin >> after_or_before;
                cout << "\nSUB List ID which you want to find: ";
                cin >> find;
                res = (after_or_before == 1) ? 
                    generalList.addBefore(sublist, find) :
                    generalList.addAfter(sublist, find);
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
                res = false;
                cout << "\nEnter SUB List ID: "; 
                cin >> SubListId;
                NodeLL *pSubListNode = generalList.findSubList(SubListId);

                if (pSubListNode == NULL)
                {
                    cout << "No such list!\n";
                    break;
                }
                cout << "\nEnter new number to add into SUB_list: ";
                cin >> new_number;
                SubList *sublist = (pSubListNode->data);
                if (sublist->isEmpty())
                {
                    sublist->pushBack(new_number);
                    res = true;
                }
                else
                {
                    cout << "1) before\n2) after\nSelect: ";
                        cin >> after_or_before;
                    cout << "\nElement which you want to find: ";
                    cin >> find;
                    res = (after_or_before == 1) ? 
                        sublist->addBefore(new_number, find) :
                        sublist->addAfter(new_number, find);
                }
                if (res) cout << "Successful!\n";
                else cout << "Item \"" << find << "\" not found. Item was not added to List\n";
            }
            break;
            
        case 3:
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

        case 5:

            if (!generalList.isEmpty()){
                cout << "\nEnter SUB List ID: "; 
                cin >> SubListId;
                NodeLL *pSubListNode = generalList.findSubList(SubListId);

                if (pSubListNode == NULL)
                {
                    cout << "No such list!\n";
                    break;
                }
                cout << "\nElement to delete: ";
                cin >> item_to_delete;
                SubList *sublist = (pSubListNode->data);
                res = sublist->removeItem(item_to_delete);
                if (res) cout << "Successful!\n";
                else cout << "Item not found\n";

            } else {
                cout << "\nList is empty. Nothing to remove.\n";
            }

            break;

        case 4:

            if (!generalList.isEmpty())
            {
                cout << "\nList ID to delete: ";
                cin >> item_to_delete;
                res = generalList.removeItem(item_to_delete);
                if (res) cout << "Successful!\n";
                else cout << "Item not found\n";
            }
            else 
            {
                cout << "\nList is empty. Nothing to remove.\n";
            }
            break;

        default:
    
            break;
        }
    }
    return 0;
}