#pragma once
#define RingQueue_h



class RingQueue
{
private:
    int *arrayPtr;
    int *first;
    int *last;
    int currentSize = 0;
    int maxSize = 0; 

public:
    RingQueue(int);
    int getCurrentSize() { return currentSize; };
    int getMaxSize() { return maxSize; }
    void addNumber(int new_number);
    void showAll();
    void removeItem();
    void printSize();
    bool isEmpty();
    ~RingQueue();

};

