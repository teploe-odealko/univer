#include <iostream>
#include "LinkedList.h"
#include <limits>

using namespace std;



int main(){
    int choice =1;
    LinkedList myLinkedList;
    

    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) Add After\n"
        "2) Add bfore\n"
        "3) Show all List forward\n"
        "4) Show all List backward\n"
        "5) Remove item\n"
        "6) Size of List\n"
        "Select: ";

        cin >> choice;

        switch (choice){

        case 1:
            int new_number;
            int paste_after;
            cout << "\nEnter new number: ";
            cin >> new_number;
            if (!myLinkedList.isEmpty()){
                
                cout << "\nEnter the item AFTER which you want to insert a new item: ";
                cin >> paste_after;
                bool result = myLinkedList.addAfter(new_number, paste_after);
                if (result) cout << "Successful!\n";
                else cout << "Item \"" << paste_after << "\" not found. Item was not added to List\n";
            } else {
                myLinkedList.pushBack(new_number);
            }

            break;
            
        case 2:
            if (!myLinkedList.isEmpty()){
                int new_number;
                int paste_before;
                cout << "\nEnter new number: ";
                cin >> new_number;
                cout << "\nEnter the item BEFORE which you want to insert a new item: ";
                cin >> paste_before;
                bool result = myLinkedList.addBefore(new_number, paste_before);
                if (result) cout << "Successful!\n";
                else cout << "Item \"" << paste_before << "\" not found. Item was not added to List\n";
            } else {
                cout << "List is Empty. Use \"Push back\" to add first item\n";
            }

            break;

        case 3:
            myLinkedList.showAllDirect();
            break;
            
        case 4:
            myLinkedList.showAllBackward();
            break;

        case 5:

            if (!myLinkedList.isEmpty()){
                int item_to_delete;
                cout << "\nEnter the the item you want to delete: ";
                cin >> item_to_delete;
                bool result = myLinkedList.removeItem(item_to_delete);
                if (result) cout << "Successful!\n";
                else cout << "Item not found\n";


            } else {
                cout << "\nArray List is empty. Nothing to remove.\n";
            }

            break;

        case 6:
            myLinkedList.printSize(); 
            break;

        default:
    
            break;
        }
        
    
    }
    return 0;

}