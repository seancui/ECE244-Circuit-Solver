//this file contains class definition and function declarations for Node class

#ifndef NODE_H
#define NODE_H

#include "ResistorList.h"

#include <string>
#include <iostream>

using namespace std;

class Node
{
private:
    int nodeNum;
    bool set; //if it has been set by setV command
    Node *next;
    ResistorList *resHead; //pointer to ResistorList object which in turn points to resistors
    double voltage;

public:
   Node(int num, Node *nextNode);
   ~Node();

   Node *getNext();
   void setNext(Node *next_);
   int getNodeNum();
   ResistorList* getHead();
   void printNode();
   void printRes(string name);
   bool findRes(string name);
   void modifyRes(string name, double resistance);
   void deleteResAll(); //delete all resistors connected to node
   void setVoltage(double V); //changes set to true
   void changeVoltage(double V); //does not change set
   void unsetVoltage();
   void deleteR(string name); //delete a specific resistor connected to node
   bool getSet();
   double getV();
};

#endif
