#include <iostream>
#include "RingQueue.h"
#include <limits>

using namespace std;



int main(){
    int choice;
    int sizeOfArray;
    cout << "\nEnter size of massive: ";
    cin >> sizeOfArray; 
    RingQueue myRingQueue(sizeOfArray);
    

    while (choice != 0){
        cout << "\nSelect action:\n" << 
        "0) Exit\n" <<
        "1) Add new number into queue\n" <<
        "2) Show all queue\n" <<
        "3) Remove one item\n" <<
        "4) Size of queue\n" <<
        "5) Is empty?\n\n" << 
        "Select: ";

        cin >> choice;

        switch (choice){

        case 1:
            if (myRingQueue.getCurrentSize() < myRingQueue.getMaxSize()){

                int new_number;
                cout << "\nEnter new number: ";
                cin >> new_number;
                myRingQueue.addNumber(new_number);
            }else{
                cout << "\nNo space. Queue is full.\n";
            }

            break;

        case 2:
            myRingQueue.showAll();
            
            break;

        case 3:
        if (!myRingQueue.isEmpty()){
            myRingQueue.removeItem();
        }else{
            cout << "\nStack is empty. Nothing to remove.\n";
        }
            break;

        case 4:
            myRingQueue.printSize(); 

            break;
        case 5:
            cout << "\nIs empty? " << bool(myRingQueue.isEmpty()) << endl;
        default:
    
            break;
        }
        
    
    }
    return 0;

}


