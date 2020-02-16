#pragma once
#define ArrayList_h



class ArrayList
{
private:
    int *arrayPtr;
    int arraySize;
    int currentSize = 0;

public:
    ArrayList(int);
    int getCurrentSize() { return currentSize; }
    int getArraySize() {return arraySize; }
    void addItem(int new_number);
    void showAll();
    void removeItem(int);
    void printSize();
    bool isEmpty();
    int findByData(int data);
    ~ArrayList();

};

