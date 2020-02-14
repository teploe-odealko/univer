#include "RingQueue.h"
#include <iostream>
using namespace std;


RingQueue::RingQueue(int sizeOfArray) {
    maxSize = sizeOfArray;
    arrayPtr = new int[sizeOfArray];
    first = arrayPtr;
    last = arrayPtr;
}


RingQueue::~RingQueue() {

}

void RingQueue::addNumber(int new_number) {
    
    *last = new_number;
    if (last == &arrayPtr[maxSize]){
        last = arrayPtr;
    } else {
        last++;
    }

    currentSize++;
    

}

void RingQueue::showAll() {
    int *current = first;
    cout << "\n----------------\nQUEUE\n\n";
    while (current != last)
    {

        cout << *current << endl;
        if (current == &arrayPtr[maxSize]){
            current = arrayPtr;
        } else{
            current++;
        }
        
    }
    cout << "\nQUEUE\n----------------\n";
}

void RingQueue::removeItem() {

    if (first == &arrayPtr[maxSize]){
        first = arrayPtr;
    } else {
        first++;
    }
    currentSize--;

}

void RingQueue::printSize() {
    cout << "\nSize of stack: " << currentSize << endl;
}

bool RingQueue::isEmpty() {
    if (currentSize == 0) return true;
    else return false;
}
