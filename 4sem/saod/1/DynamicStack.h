#pragma once
// #define DynamicStack_h0

struct Node
{
    Node *next = nullptr;
    int data;
};

class DynamicStack
{
private:
    int size = 0; 
    Node* sp = nullptr;
public:
    DynamicStack(/* args */);
    Node* getSp(){ return sp; };
    void addNumber(int new_number);
    void showAll();
    void removeTop();
    void printSize();
    bool isEmpty();
    ~DynamicStack();

};

