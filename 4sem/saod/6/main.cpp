#include <iostream>
#include "DynamicList.h"
#include <limits>

using namespace std;



int main(){
    int choice =1;
    DynamicList myDynamicList;
    

    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) Push back\n"
        "2) Push after\n"
        "3) Push before\n"
        "4) Show all List\n"
        "5) Remove item\n"
        "6) Size of List\n"
        "7) Is empty?\n" 
        "8) Show additional stack\n"
        "Select: ";

        cin >> choice;

        switch (choice){

        case 1:
            
            int new_number;
            cout << "\nEnter new number: ";
            cin >> new_number;
            myDynamicList.pushBack(new_number);
            cout << "Successful!\n";
            
            break;
        case 2:
            
            if (!myDynamicList.isEmpty()){
                int new_number;
                int paste_after;
                cout << "\nEnter new number: ";
                cin >> new_number;
                cout << "\nEnter the item AFTER which you want to insert a new item: ";
                cin >> paste_after;
                bool result = myDynamicList.addAfter(new_number, paste_after);
                if (result) cout << "Successful!\n";
                else cout << "Item \"" << paste_after << "\" not found. Item was not added to List\n";
            } else {
                cout << "List is Empty. Use \"Push back\" to add first item\n";
            }

            break;

        case 3:

            if (!myDynamicList.isEmpty()){
                int new_number;
                int paste_before;
                cout << "\nEnter new number: ";
                cin >> new_number;
                cout << "\nEnter the item BEFORE which you want to insert a new item: ";
                cin >> paste_before;
                bool result = myDynamicList.addBefore(new_number, paste_before);
                if (result) cout << "Successful!\n";
                else cout << "Item \"" << paste_before << "\" not found. Item was not added to List\n";
            } else {
                cout << "List is Empty. Use \"Push back\" to add first item\n";
            }

            break;


        case 4:
            myDynamicList.showAll();
            break;

        case 5:

            if (!myDynamicList.isEmpty()){
                int item_to_delete;
                cout << "\nEnter the the item you want to delete: ";
                cin >> item_to_delete;
                bool result = myDynamicList.removeItem(item_to_delete);
                if (result) cout << "Successful!\n";
                else cout << "Item not found\n";


            } else {
                cout << "\nArray List is empty. Nothing to remove.\n";
            }

            break;

        case 6:
            myDynamicList.printSize(); 
            break;

        case 7:
            cout << "\nIs empty? " << bool(myDynamicList.isEmpty()) << endl;
            break;

        case 8:
            myDynamicList.showStack();
            break;
        default:
    
            break;
        }
        
    
    }
    return 0;

}