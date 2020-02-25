#include <iostream>
#include "DynamicQueue.h"
#include <limits>
#include <random>

using namespace std;



int main(){
    char ch;
    char quit = 'x';

    DynamicQueue myDynamicQueue;
    
    default_random_engine generator;
    uniform_int_distribution<int> dist1_100(1,100);
    uniform_int_distribution<int> dist1_3(1,3);
    cout << "\nQueue and random_genetator initialized.\n";

    while (quit != 'q'){
        if (myDynamicQueue.isEmpty())
        {
            int amount_chars = dist1_3(generator);
            cout << amount_chars <<" items have been added\n";
            for (int i = 0; i < amount_chars; i++)
            {
                ch = 'A' + rand()%26;
                myDynamicQueue.addItem(ch);
            }
        } 
        else

        {
            int add_or_remove = dist1_100(generator) % 2;
            int amount_chars = dist1_3(generator);
            if(add_or_remove){
                for (int i = 0; i < amount_chars; i++)
                {
                    ch = 'A' + rand()%26;
                    myDynamicQueue.addItem(ch);
                    cout << amount_chars <<" items have been added\n";

                }
            }else{
                cout << amount_chars <<" items have been removed\n";

                for (int i = 0; i < amount_chars; i++)
                {
                    myDynamicQueue.removeItem();

                }
            }
        }
        myDynamicQueue.showAll();
        cout << "\nQ - quit, Enter - continue\n";
        cin >> quit;
    }
    
    
    

    // while (choice != 0){
    //     cout << "\nSelect action:\n" << 
    //     "0) Exit\n" <<
    //     "1) Add new number into queue\n" <<
    //     "2) Show all queue\n" <<
    //     "3) Remove one item\n" <<
    //     "4) Size of queue\n" <<
    //     "5) Is empty?\n\n" << 
    //     "Select: ";

    //     cin >> choice;

    //     switch (choice){

    //     case 1:
    //         if (myDynamicQueue.getCurrentSize() < myDynamicQueue.getMaxSize()){

    //             int new_number;
    //             cout << "\nEnter new number: ";
    //             cin >> new_number;
    //             myDynamicQueue.addItem(new_number);
    //         }else{
    //             cout << "\nNo space. Queue is full.\n";
    //         }

    //         break;

    //     case 2:
    //         myDynamicQueue.showAll();
            
    //         break;

    //     case 3:
    //     if (!myDynamicQueue.isEmpty()){
    //         myDynamicQueue.removeItem();
    //     }else{
    //         cout << "\nStack is empty. Nothing to remove.\n";
    //     }
    //         break;

    //     case 4:
    //         myDynamicQueue.printSize(); 

    //         break;
    //     case 5:
    //         cout << "\nIs empty? " << bool(myDynamicQueue.isEmpty()) << endl;
    //     default:
    
    //         break;
    //     }
        
    
    // }
    return 0;

}