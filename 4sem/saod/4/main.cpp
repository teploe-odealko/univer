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
        "1) Add new number into Array List\n" <<
        "2) Show all Array List\n" <<
        "3) Remove one item\n" <<
        "4) Size of Array List\n" <<
        "5) Is empty?\n" << 
        "6) Find by data\n\n" <<
        "Select: ";

        cin >> choice;

        switch (choice){

        case 1:
            if (myArrayList.getArraySize() > myArrayList.getCurrentSize()) {
                int new_number;
                cout << "\nEnter new number: ";
                cin >> new_number;
                myArrayList.addItem(new_number);
                cout << "Successful!\n";

            } else {
                cout << "\nNo space. Array List is full.\n";
            }
            break;

        case 2:
            myArrayList.showAll();
            break;

        case 3:

            if (!myArrayList.isEmpty()){
                int index;
                cout << "\nEnter the index of the item you want to delete: ";
                cin >> index;
                myArrayList.removeItem(index);
                cout << "Successful!\n";

            } else {
                cout << "\nArray List is empty. Nothing to remove.\n";
            }

            break;

        case 4:
            myArrayList.printSize(); 

            break;
        case 5:
            cout << "\nIs empty? " << bool(myArrayList.isEmpty()) << endl;
            break;

        case 6:
            if (!myArrayList.isEmpty()){
                int search;
                cout << "\nEnter data to search: ";
                cin >> search;
                int index = myArrayList.findByData(search);
                if (index >= 0){
                    cout << "Inem \"" << search << "\" have index " << index << endl;
                } else {
                    cout << "Item \"" << search << "\" not listed!\n";
                }
                
            } else {
                cout << "\nArray List is empty.\n";
            }

            break;
        default:
    
            break;
        }
        
    
    }
    return 0;

}


