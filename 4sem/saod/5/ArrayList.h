#pragma once
#define ArrayList_h

struct Node
{
    int next = -1;
    int data;
};



class ArrayList
{
private:
    Node *arrayPtr;
    int arraySize;
    int currentSize = 0;
    int firstFreeCell();

public:
    ArrayList(int);
    int getCurrentSize() { return currentSize; }
    int getArraySize() {return arraySize; }
    bool addAfter(int, int) ;
    bool addBefore(int, int);
    void pushBack(int);
    void showAll();
    bool removeItem(int);
    void printSize();
    bool isEmpty();
    int findByData(int data);
    ~ArrayList();

};

