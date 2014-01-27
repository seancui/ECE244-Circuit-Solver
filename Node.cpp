//this file contains definitions of functions for Node class

#include "Node.h"
#include <iomanip>

Node::Node(int num, Node *nextNode){
    nodeNum = num;
    set = false;
    next = nextNode;
    resHead = new ResistorList;
    voltage = 0;
}

Node::~Node(){
    delete resHead; //because "new" is used in constructor, "delete" is need here to prevent memory leak
}

Node* Node::getNext(){
    return next;
}
void Node::setNext(Node *next_){
    next = next_;
}

int Node::getNodeNum(){
    return nodeNum;
}

ResistorList* Node::getHead(){
    return resHead;
}

void Node::printNode(){
    cout << "Connections at node " << nodeNum << ": " << resHead->countResistors() << " resistor(s)" << endl;
    resHead->printRAll();
}

void Node::printRes(string name){
    resHead->printR(name);
}

bool Node::findRes(string name){
    return resHead->findR(name);
}

void Node::modifyRes(string name, double resistance){
    resHead->modifyR(name, resistance);
}

void Node::deleteResAll(){
    resHead->deleteRAll();
}

void Node::setVoltage(double V){
    voltage = V;
    set = true;
}

void Node::changeVoltage(double V){
    voltage = V;
}

void Node::unsetVoltage(){
    set = false;
}

void Node::deleteR(string name){
    resHead->deleteR(name);
}

bool Node::getSet(){
    return set;
}

double Node::getV(){
    return voltage;
}
