#include "ArrayList.h"
#include <iostream>
using namespace std;


ArrayList::ArrayList(int sizeOfArray) {
    arraySize = sizeOfArray;
    arrayPtr = new int[sizeOfArray];
    
}


ArrayList::~ArrayList() {

}



void ArrayList::addItem(int new_number) {

    int i;
    for (i = 0; i < currentSize; i++){   // Поиск места для вставки нового элемента
        if (arrayPtr[i] > new_number){
            break;
        }
    }

    for (int j = 0; j < (currentSize - i); j++){ //  Сдвиг элеметов вправо
        arrayPtr[currentSize - j] = arrayPtr[currentSize - 1 - j];
    }

    arrayPtr[i] = new_number;
    currentSize++;

}


void ArrayList::showAll() {
    cout << "\n----------------\nBegin of ArrayList\n\n";
    for (int i = 0; i < currentSize; i++){
        cout << arrayPtr[i] << endl;
    }
    cout << "\nEnd of ARRAY LIST\n----------------\n";
}


void ArrayList::removeItem(int index) {


    if (currentSize -1 < index){
        cout << endl << index <<" Item does not exist. Last index " << currentSize-1 << endl;  
    } else {
        for (int i=0; i < currentSize - index - 1; i++){
            arrayPtr[index + i] = arrayPtr[index + i + 1];
        }
        currentSize--;
    }
        

 
    
}

void ArrayList::printSize() {
    cout << "\nSize of stack: " << currentSize << endl;
}

bool ArrayList::isEmpty() {
    if (currentSize == 0) return true;
    else return false;
}

int ArrayList::findByData(int data){
    for (int i=0; i < currentSize; i++){
        if(data == arrayPtr[i]){
            return i;
        }
    }
    return -1;

}
