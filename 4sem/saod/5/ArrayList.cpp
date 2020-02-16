#include "ArrayList.h"
#include <iostream>
using namespace std;




ArrayList::ArrayList(int sizeOfArray) {
    arraySize = sizeOfArray;
    arrayPtr = new Node[sizeOfArray + 1];
    arrayPtr[0].next = 0;
    
}


ArrayList::~ArrayList() {

}

int ArrayList::firstFreeCell(){
    int j;
    for (j = 0; j < arraySize; j++){   // Поиск первой свободной ячейки
        if (arrayPtr[j+1].next == -1 ){
            return j+1;
        }    
    }
    return -1;
}

bool ArrayList::removeItem(int item_to_delete) {

    int current = arrayPtr[0].next;
    int previous = 0;
    while (current != 0){
        if (arrayPtr[current].data == item_to_delete){
            arrayPtr[previous].next = arrayPtr[current].next;
            arrayPtr[current].next = -1;
            currentSize--;
            return true;
        }
        previous = current;
        current = arrayPtr[current].next;
    }
    return false;
    
}


void ArrayList::pushBack(int new_item){
    int freeCell = firstFreeCell();
    int current = arrayPtr[0].next;
    for (int i = 0; i < currentSize - 1; i++){
        current = arrayPtr[current].next;
    }
    arrayPtr[freeCell].data = new_item;
    arrayPtr[freeCell].next = 0;
    arrayPtr[current].next = freeCell;
    currentSize++;
}

bool ArrayList::addAfter(int new_number, int paste_after) {
    
    int j = firstFreeCell();
    arrayPtr[j].data = new_number;
    int current = arrayPtr[0].next;
    while (current != 0){
        if (arrayPtr[current].data == paste_after){
            arrayPtr[j].next = arrayPtr[current].next;
            arrayPtr[current].next = j;
            currentSize++;
            return true;
        }
        current = arrayPtr[current].next;
    }
    return false;   
}

bool ArrayList::addBefore(int new_number, int paste_before) {
    
    int j = firstFreeCell();
    arrayPtr[j].data = new_number;
    int current = arrayPtr[0].next;
    int previous = 0;
    
    while (current != 0){
        if (arrayPtr[current].data == paste_before){
            arrayPtr[j].next = current;
            arrayPtr[previous].next = j;
            currentSize++;
            return true;
        }

        previous = current;
        current = arrayPtr[current].next;
    }
    return false;   
}


void ArrayList::showAll() {
    int current = arrayPtr[0].next;
    cout << "\n----------------\nBegin of ArrayList\n\n";
    while (current != 0){
        cout << arrayPtr[current].data << endl;
        current = arrayPtr[current].next;
    }
    cout << "\nEnd of ARRAY LIST\n----------------\n";
}


void ArrayList::printSize() {
    cout << "\nSize of List: " << currentSize << endl;
}

bool ArrayList::isEmpty() {
    if (currentSize == 0) return true;
    else return false;
}

// int ArrayList::findByData(int data){
//     for (int i=0; i < currentSize; i++){
//         if(data == arrayPtr[i]){
//             return i;
//         }
//     }
//     return -1;

// }
