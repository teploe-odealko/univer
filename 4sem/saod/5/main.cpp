#include <iostream>
#include "ArrayList.h"
#include <limits>

using namespace std;



int main(){
    int choice =1;
    int sizeOfArray;
    cout << "\nEnter size of massive: ";
    cin >> sizeOfArray; 
    ArrayList myArrayList(sizeOfArray);
    

    while (choice != 0){
        cout << "\nSelect action:\n" << 
        "0) Exit\n" <<
        "1) Push back\n" <<
        "2) Push after\n" <<
        "3) Push before\n" <<
        "4) Show all Array List\n" <<
        "5) Remove item\n" <<
        "6) Size of Array List\n" <<
        "7) Is empty?\n" << 
        "Select: ";

        cin >> choice;

        switch (choice){

        case 1:
            if (myArrayList.getArraySize() > myArrayList.getCurrentSize()) {
                
                    int new_number;
                    cout << "\nEnter new number: ";
                    cin >> new_number;
                    myArrayList.pushBack(new_number);
                    cout << "Successful!\n";
                
            } else {
                cout << "\nNo space. Array List is full.\n";
            }
            break;
        case 2:
            if (myArrayList.getArraySize() > myArrayList.getCurrentSize()) {
                if (!myArrayList.isEmpty()){
                    int new_number;
                    int paste_after;
                    cout << "\nEnter new number: ";
                    cin >> new_number;
                    cout << "\nEnter the item AFTER which you want to insert a new item: ";
                    cin >> paste_after;
                    bool result = myArrayList.addAfter(new_number, paste_after);
                    if (result) cout << "Successful!\n";
                    else cout << "Item \"" << paste_after << "\" not found. Item was not added to List\n";
                } else {
                    cout << "List is Empty. Use \"Push back\" to add first item\n";
                }
            } else {
                cout << "\nNo space. Array List is full.\n";
            }
            break;

        case 3:
            if (myArrayList.getArraySize() > myArrayList.getCurrentSize()) {
                if (!myArrayList.isEmpty()){
                    int new_number;
                    int paste_before;
                    cout << "\nEnter new number: ";
                    cin >> new_number;
                    cout << "\nEnter the item BEFORE which you want to insert a new item: ";
                    cin >> paste_before;
                    bool result = myArrayList.addBefore(new_number, paste_before);
                    if (result) cout << "Successful!\n";
                    else cout << "Item \"" << paste_before << "\" not found. Item was not added to List\n";
                } else {
                    cout << "List is Empty. Use \"Push back\" to add first item\n";
                }
            } else {
                cout << "\nNo space. Array List is full.\n";
            }
            break;


        case 4:
            myArrayList.showAll();
            break;

        case 5:

            if (!myArrayList.isEmpty()){
                int item_to_delete;
                cout << "\nEnter the the item you want to delete: ";
                cin >> item_to_delete;
                bool result = myArrayList.removeItem(item_to_delete);
                if (result) cout << "Successful!\n";
                else cout << "Item not found\n";


            } else {
                cout << "\nArray List is empty. Nothing to remove.\n";
            }

            break;

        case 6:
            myArrayList.printSize(); 

            break;
        case 7:
            cout << "\nIs empty? " << bool(myArrayList.isEmpty()) << endl;
            break;

        case 8:
            // if (!myArrayList.isEmpty()){
            //     int search;
            //     cout << "\nEnter data to search: ";
            //     cin >> search;
            //     int index = myArrayList.findByData(search);
            //     if (index >= 0){
            //         cout << "Inem \"" << search << "\" have index " << index << endl;
            //     } else {
            //         cout << "Item \"" << search << "\" not listed!\n";
            //     }
                
            // } else {
            //     cout << "\nArray List is empty.\n";
            // }

            break;
        default:
    
            break;
        }
        
    
    }
    return 0;

}


