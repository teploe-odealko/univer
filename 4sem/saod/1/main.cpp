#include <iostream>
#include "DynamicStack.h"

using namespace std;

int main(){
    int choice; 
    DynamicStack firstStack;
    DynamicStack secondStack;
    

    while (choice != 0){
        cout << "\nSel1ect action:\n" << 
        "0) Exit\n" <<
        "1) Add new number into stack\n" <<
        "2) Show all numbers\n" <<
        "3) Remove from top of stack \n" <<
        "4) Size of stack\n" <<
        "5) Is empty?\n";
        cin >> choice;

        switch (choice){
        case 1:
            int new_number;
            cin >> new_number;
            firstStack.addNumber(new_number);
            break;
        case 2:
            firstStack.showAll();
            break;
        case 3:
        if (!firstStack.isEmpty()){
            int choice2;
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

        case 5:

        default:
            break;
        }
        // cout << "hi" << endl;
        
    }
    
    return 0;
    
}


