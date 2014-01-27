//this file contains class definition and function declarations for NodeList class

#ifndef NODELIST_H
#define NODELIST_H

#include "Node.h"
#include "ResistorList.h"

#include <string>
#include <iostream>

using namespace std;

class NodeList{
    private:
        Node* nodeHead;
    public:
        NodeList();
        void insertNode(int nodeNum_);
        bool nodeExists(int nodeNum); //checks if node with number nodeNum exists
        Node* findNode(int nodeNum);
        Node* getHead();
        void printR(string name);
        int getSize();
};

#endif
