#include "UsersList.h"
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;


UsersList::UsersList(int sizeOfArray, string op_name) {
    max_num_of_users = sizeOfArray;
    users = new UserNode[sizeOfArray];
    operator_name = op_name;
    
}


UsersList::~UsersList() {
    delete[] users;
}


void UsersList::add_user(string last_name, string phone_model) {

    int i;
    for (i = 0; i < current_num_of_users; i++){   // Поиск места для вставки нового элемента
        if (users[i].last_name > last_name){
            break;
        }
    }

    for (int j = 0; j < (current_num_of_users - i); j++){ //  Сдвиг элеметов вправо
        users[current_num_of_users - j] = users[current_num_of_users - 1 - j];
    }

    users[i].last_name = last_name;
    users[i].phone_model = phone_model;
    current_num_of_users++;

}


void UsersList::show_all_users() {
    for (int i = 0; i < current_num_of_users; i++){
        cout    << users[i].last_name 
                << "-"
                << users[i].phone_model
                << endl;
    }
}

void UsersList::to_file(ofstream& fout) {
    for (int i = 0; i < current_num_of_users; i++){
        fout    << users[i].last_name 
                << "-"
                << users[i].phone_model
                << endl;
    }
}


bool UsersList::remove_user(string last_name) {
    int index = findByData(last_name);
    if (-1 == index){
        return false;  
    } else {
        for (int i=0; i < current_num_of_users - index - 1; i++){
            users[index + i] = users[index + i + 1];
        }
        current_num_of_users--;
    }
    return true;

}

bool UsersList::isEmpty() {
    if (current_num_of_users == 0) return true;
    else return false;
}

int UsersList::findByData(string last_name){
    for (int i=0; i < current_num_of_users; i++){
        if(last_name == users[i].last_name){
            return i;
        }
    }
    return -1;

}
