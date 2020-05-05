#include <iostream>
#include "OperatorsList.h"
#include "UsersList.h"
#include <string>
using namespace std;

int main()
{
    int choice = 1;
    OperatorsList operatorsList;

    while (choice != 0)
    {
        cout << "\nselect an action:\n"
                "0) Exit\n"
                "1) Add a new operator\n"
                "2) Add a new user for the operator\n"
                "3) Show the entire list\n"
                "4) Delete the operator\n"
                "5) Delete the user from the selected operator\n"
                "6) Download from the file\n"
                "7) Upload to file\n"
                "Select: ";
        cin >> choice;
        cout << endl;
        bool res;
        string operator_name, find, phone_model, last_name;

        switch (choice)
        {
            int user_amount;

        case 1:
        {

            cout << " Enter the operator name: ";
            cin >> operator_name;
            cout << "\nHow many users does this operator have?: ";
            cin >> user_amount;
            UsersList *sublist = new UsersList(user_amount, operator_name);
            operatorsList.add_operator(sublist);
            break;
        }
        case 2:
            if (operatorsList.isEmpty())
            {
                cout << "\nthere are no operators Yet. Create or upload from the file\n";
            }
            else
            {
                res = false;
                cout << "\n enter the operator name to add the user: ";
                cin >> operator_name;
                NodeLL *pSubListNode = operatorsList.findUsersList(operator_name);

                if (pSubListNode == NULL)
                {
                    cout << "\nthere is no such operator yet!\n";
                    break;
                }

                UsersList *sublist = (pSubListNode->data);
                if (sublist->get_current_num_of_users() < sublist->get_max_num_of_users())
                {
                    cout << "\nenter the user's last name: ";
                    cin >> last_name;
                    cout << "\nenter the user's phone brand: ";
                    cin >> phone_model;
                    sublist->add_user(last_name, phone_model);
                    res = true;
                }
                if (res)
                    cout << " Completed!\n";
                else
                    cout << " List is full\n";
            }
            break;

        case 3:
            if (operatorsList.isEmpty())
            {
                cout << "\nthere are no operators Yet. Create or upload from the\n file";
            }
            else
            {
                operatorsList.show_all();
                cout << endl;
            }
            break;

        case 5:

            if (!operatorsList.isEmpty())
            {
                cout << "\nPlease enter the name of the operator: ";
                cin >> operator_name;
                NodeLL *pSubListNode = operatorsList.findUsersList(operator_name);

                if (pSubListNode == NULL)
                {
                    cout << "\nthere is no such operator yet!\n";
                    break;
                }
                cout << " \n username to delete: ";
                cin >> last_name;
                UsersList *sublist = (pSubListNode->data);
                res = sublist->remove_user(last_name);
                if (res)
                    cout << " Completed!\n";
                else
                    cout << " User not found\n";
            }
            else
            {
                cout << "\nthis operator doesn't have any users yet\n";
            }

            break;

        case 4:

            if (!operatorsList.isEmpty())
            {
                cout << "\n enter the name of the operator you want to delete: ";
                cin >> operator_name;
                res = operatorsList.remove_operator(operator_name);
                if (res)
                    cout << " Completed!\n";
                else
                    cout << "there is no such operator yet\n";
            }
            else
            {
                cout << " \n there is no operator. Nothing to delete\n";
            }
            break;

        case 6:
            operatorsList.from_file(operatorsList);
            break;

        case 7:
            operatorsList.to_file();
            break;

        default:
            break;
        }
    }
    return 0;
}