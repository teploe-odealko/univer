#pragma once
#include "UsersList.h"
#define OperatorsList_h
#include <string>

struct NodeLL
{
    NodeLL* right;
    NodeLL* left;
    UsersList* data;
};

class OperatorsList
{
private:
    int current_num_of_operators = 0;
    NodeLL* pHead;
    
public:
    OperatorsList();
    NodeLL *findUsersList(string);
    void add_operator(UsersList*);
    void show_all();
    void to_file();
    void from_file(OperatorsList&);
    bool remove_operator(string);
    bool isEmpty();
    ~OperatorsList();
};

