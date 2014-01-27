//this file contains function definitions for ResistorList class

#include <iomanip>
#include "ResistorList.h"

ResistorList::ResistorList(){
    resHead = NULL;
}

void ResistorList::insertR(string nameArg, double resistance, int endPoint1, int endPoint2){
    Resistor *cur = resHead;
    if(cur == NULL){ //if list is empty create new resistor and point head to it
        Resistor* res = new Resistor(nameArg, resistance, endPoint1, endPoint2, NULL);
        resHead = res;
    }
    else{ //goes to end of list and adds to the end
        while(cur->getNext() != NULL)
            cur = cur->getNext();
        Resistor* res = new Resistor(nameArg, resistance, endPoint1, endPoint2, NULL);
        cur->setNext(res);
    }
}

bool ResistorList::deleteR(string name){
    Resistor *cur = resHead;
    Resistor *prev;
    while(cur != NULL){
        if (cur->getName() == name){
            if (cur == resHead && cur->getNext() != NULL){ //more than 1 object in list and want to delete first object
                Resistor  *tmp = resHead;
                resHead = resHead->getNext();
                delete tmp;
                return true;
            }
            else if (cur == resHead && cur->getNext() == NULL){ //only 1 object in list
                Resistor  *tmp = resHead;
                delete tmp;
                resHead = NULL;
                return true;
            }
            else if (cur != resHead && cur->getNext() == NULL){ //if at end of list
                delete cur;
                prev->setNext(NULL);
                return false;
            }
            else{ //if in middle of list
                prev->setNext(cur->getNext());
                delete cur;
                return false;
            }
        }
        prev = cur;
        cur = cur->getNext();
    }
}

void ResistorList::printRAll(){
    Resistor *cur = resHead;
    while(cur != NULL){
        cout << "  ";
        cur->print();
        cur = cur->getNext();
    }
}

int ResistorList::countResistors(){
    int count = 0;
    Resistor *cur = resHead;
    while(cur != NULL){
        count += 1;
        cur = cur->getNext();
    }
    return count;
}

void ResistorList::printR(string name){
    Resistor *cur = resHead;
    while(cur != NULL){
        if (cur->getName() == name){
            cout << "Print:" << endl;
            cur->print();
        }
        cur = cur->getNext();
    }
}

bool ResistorList::findR(string name){
    Resistor *cur = resHead;
    while(cur != NULL){
        if (cur->getName() == name){
            return true;
        }
        cur = cur->getNext();
    }
    return false;
}

void ResistorList::modifyR(string name, double resistance){
    Resistor *cur = resHead;
    while(cur != NULL){
        if (cur->getName() == name){
            cur->setResistance(resistance);
        }
        cur = cur->getNext();
    }
}

void ResistorList::deleteRAll(){
    Resistor *cur = resHead;
    Resistor *prev;
    while(cur != NULL){ //keeps track of previous and current node. cur moves to next node, delete previous
        prev = cur;
        cur = cur->getNext();
        delete prev;
    }
    resHead = NULL; //set to NULL for safety
}

Resistor* ResistorList::findResPoint(string name){
    Resistor *cur = resHead;
    while(cur != NULL){
        if (cur->getName() == name){
            return cur; //returns pointer to needed resistor
        }
        cur = cur->getNext();
    }
    return NULL; //if not found return NULL
}

int ResistorList::getSize(){
    int size = 0;
    Resistor *cur = resHead;
    while(cur != NULL){
        size += 1;
        cur = cur->getNext();
    }
    return size;
}

double ResistorList::makeFirstTerm(){
    double denominator = 0;
    Resistor *cur = resHead;
    while(cur != NULL){
        denominator += 1/(cur->getResistance()); //according to equation; make denominator
        cur = cur->getNext();
    }
    return 1/denominator; //returns 1/denominator as according to equation
}

Resistor* ResistorList::getHead(){
    return resHead;
}
