#include <iostream>
#include "DynamicStack.h"
#include <limits>
#include <random>

using namespace std;



int main(){
    default_random_engine generator;
    uniform_int_distribution<int> dist1_100(1,100);
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
        "5) Is empty?\n" << 
        "6) Add several items\n\n"
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
                    firstStack.addNode(secondStack.getTopPtr());
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
                secondStack.addNode(firstStack.getTopPtr());
            } else {
                firstStack.removeTop();
            }
            
        }else{
            cout << "\nStack is empty. Nothing to remove.\n";
        }
            break;

        case 4:
            firstStack.printSize(); 

            break;
        case 5:
            cout << "\nIs empty? " << bool(firstStack.isEmpty()) << endl;
            break;

        case 6:
            int n, tmpAdd;
            cout << "Enter amaunt of numbers: ";
            cin >> n;
            for (int i = 0; i < n; i++){
                tmpAdd = dist1_100(generator);
                firstStack.addNumber(tmpAdd);
            }
        default:

            break;
        }
        
    
    }
    return 0;

}


