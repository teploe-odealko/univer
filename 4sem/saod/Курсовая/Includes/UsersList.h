#pragma once
#define UsersList_h
#include <string>
using namespace std;


struct UserNode
{
    string last_name;
    string phone_model;
};

class UsersList
{
private:
    UserNode *users;
    int max_num_of_users;
    int current_num_of_users = 0;

public:
    string operator_name;
    UsersList(int, string);
    int get_current_num_of_users() { return current_num_of_users; }
    int get_max_num_of_users() {return max_num_of_users; }
    void add_user(string, string);
    void show_all_users();
    void to_file(ofstream&);
    bool remove_user(string);
    bool isEmpty();
    int findByData(string);
    ~UsersList();

};

