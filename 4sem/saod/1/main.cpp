#include <iostream>
#include "DynamicStack.h"
#include <limits>

using namespace std;



int main(){
    int choice; 
    DynamicStack firstStack;
    DynamicStack secondStack;
    

    while (choice != 0){
        cout << "\nSelect action:\n" << 
        "0) Exit\n" <<
        "1) Add new number into stack\n" <<
        "2) Show all stack\n" <<
        "3) Remove from top of stack \n" <<
        "4) Size of stack\n" <<
        "5) Is empty?\n\n" << 
        "Select: ";

        cin >> choice;

        switch (choice){

        int choice2;
        case 1:
            
            cout << "\nSel1ect action:\n" << 
                "0) Add new number\n" <<
                "1) Add from second stack\n";
            cin >> choice2;
            if (choice2){
                if (!secondStack.isEmpty())
                {
                    firstStack.addNumber(secondStack.getSp() -> data);
                    secondStack.removeTop();
                } 
                else
                {        
                    cout << "Second (additional) stack is empty\n";
                }
                
                
            }else{
                int new_number;
                cout << "\nEnter new number: ";
                cin >> new_number;
                firstStack.addNumber(new_number);
            }
            break;

        case 2:
            cout << "\nSel1ect action:\n" << 
                "0) First (main) stack\n" <<
                "1) Second (additional) stack\n";
            cin >> choice2;
            if (choice2){
                secondStack.showAll();
            }else{
                firstStack.showAll();
            }
            
            break;

        case 3:
        if (!firstStack.isEmpty()){
            cout << "\nSel1ect action:\n" << 
                "0) Remove\n" <<
                "1) Move to second Stack\n";
            cin >> choice2;
            if (choice2){
                secondStack.addNumber(firstStack.getSp() -> data);
            }
            firstStack.removeTop();
            
        }else{
            cout << "\nStack is empty. Nothing to remove.\n";
        }
            break;

        case 4:
            firstStack.printSize(); 

            break;
        case 5:
            cout << "\nIs empty? " << bool(firstStack.isEmpty()) << endl;
        default:
    
            break;
        }
        
    
    }
    return 0;

}


