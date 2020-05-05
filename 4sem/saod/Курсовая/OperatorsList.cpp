#include "OperatorsList.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

OperatorsList::OperatorsList()
{
    pHead = new NodeLL();
    pHead->right = pHead;
    pHead->left = pHead;
}

OperatorsList::~OperatorsList() {
    
}
 
void OperatorsList::show_all() 
{
    NodeLL *current_list = pHead -> right;
    UsersList *subList;
    cout << "----------------\n";
    while (current_list != pHead)
    {
        subList = current_list->data;
        cout << "Operator \"" << subList->operator_name << "\"" << endl;
        subList->show_all_users();
        cout << "----------------\n";
        current_list = current_list->right;
    }
}




bool OperatorsList::remove_operator(string item_to_remove) {
    NodeLL* pCurrent = pHead->right;

    while ((pCurrent != pHead) && (pCurrent->data)->operator_name != item_to_remove) {
        pCurrent = pCurrent->right;
    }
    if (pCurrent == pHead){ // Если заданного элемента нет в списке
        return false;
    } else {  
        pCurrent->left->right = pCurrent->right;
        pCurrent->right->left = pCurrent->left;
        pCurrent->data->~UsersList();
        delete pCurrent;
        current_num_of_operators--;
        return true;
    }
}


bool OperatorsList::isEmpty() 
{
    if (pHead -> right == pHead) return true;
    else return false;
}


void OperatorsList::add_operator(UsersList *new_item) {
    
    NodeLL *pCurrent = pHead->right;
    while ((pCurrent != pHead) && (pCurrent->data)->operator_name < new_item->operator_name)
    {
        pCurrent = pCurrent->right;
    }

    NodeLL* pTemp = new NodeLL();

    pTemp->data = new_item;
    pTemp->right = pCurrent;
    pTemp->left = pCurrent->left;
    pCurrent->left->right = pTemp;
    pCurrent->left = pTemp;
    current_num_of_operators++;


}

NodeLL *OperatorsList::findUsersList(string searchBy)
{
    NodeLL *pCurrent = pHead->right;
    while ((pCurrent != pHead) && (pCurrent->data)->operator_name != searchBy)
    {
        pCurrent = pCurrent->right;
    }
    if (pCurrent == pHead)
        pCurrent = NULL;
    return pCurrent;
}

string get_last_name(string user_data)
{
    string::size_type pos = user_data.find('-');
    return user_data.substr(0, pos);
    
}

string get_phone_model(string user_data)
{
    string::size_type pos = user_data.find('-');
    return user_data.substr(pos+1, user_data.size());

}

void OperatorsList::from_file(OperatorsList &OperatorsList) 
{
    string operator_name, users_amount_string, user_data;
    int users_amount;
    std::ifstream in("base.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, operator_name))
        {
            getline(in, users_amount_string);
            users_amount = stoi(users_amount_string);
            UsersList *sublist = new UsersList(users_amount, operator_name);
            for (int i = 0; i < users_amount; i++)
            {
                getline(in, user_data);
                sublist->add_user(get_last_name(user_data), get_phone_model(user_data));
            }
            OperatorsList.add_operator(sublist);
            // users_amount = 
            // std::cout << line << std::endl;
        }
    }
    in.close();     // закрываем файл
}

void OperatorsList::to_file() 
{
    NodeLL *current_list = pHead -> right;
    UsersList *subList;
    ofstream fout;
    fout.open("file.txt");
    // fout << "----------------\n";
    while (current_list != pHead)
    {
        subList = current_list->data;
        fout    << subList->operator_name << endl
                << subList->get_current_num_of_users()
                << endl;
        subList->to_file(fout);
        // cout << "----------------\n";
        current_list = current_list->right;
    }
    fout.close();
    // cout << "\nLAST LIST\n----------------\n";
}