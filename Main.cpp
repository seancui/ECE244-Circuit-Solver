//Shimeng Cui 999850406
//For lab 4 of course ECE244
//For this lab, the program must take in a command and arguments from the user and then perform an action as needed. Error messages will be outputted
//if the action cannot be performed. The program will create a linked lists of nodes and resistors to store those objects. Node and resistors will be
//added and deleted at the command of the user. The program will also have a solver function that will determine the unknown voltage of nodes that
//were not set by the user.

#include <iostream> //standard header files to allow for use of strings, stringstreams, etc.
#include <string>
#include <sstream>
#include <iomanip> //used for set precision, align left and right and set padding
#include <cmath> //needed for absolute value function

#include "Rparser.h"
#include "Node.h"
#include "Resistor.h"
#include "ResistorList.h"
#include "NodeList.h"

#define MIN_ITERATION_CHANGE 0.0001

using namespace std;

int main(){
    NodeList nodeList; //NodeList object that points to list of nodes

    cout.setf (ios::fixed); //make sure everything prints as decimals and not scientific notation

    string userInputOriginal;
    double resistance, voltage;
    int intArg1, intArg2; //used temporrarily to store any integer user inputs

    while (!cin.eof()){
        string command, stringArg; //variables for string arguments. Inside loop because I need to reinitate to null string every loop through

        cout << "> ";

        if (cin.eof()) //if end of file, exit loop
            break;

        getline(cin,userInputOriginal); //gets user input.
        stringstream userInput (userInputOriginal);

        userInput >> command;

        if (command == "insertR"){
            userInput >> stringArg >> resistance >> intArg1 >> intArg2;
            if (nodeList.nodeExists(intArg1) == true && nodeList.nodeExists(intArg2) == true){ //if both nodes exist already
                nodeList.findNode(intArg1)->getHead()->insertR(stringArg, resistance, intArg1, intArg2); //insert into already existing node
                nodeList.findNode(intArg2)->getHead()->insertR(stringArg, resistance, intArg1, intArg2);
                cout << "Inserted: resistor " << stringArg << " " << setprecision(2) << resistance << " Ohms " << intArg1 << " -> " << intArg2 << endl;
            }
            else if (nodeList.nodeExists(intArg1) == false && nodeList.nodeExists(intArg2) == true){ //checks if one of the nodes does not exist
                nodeList.insertNode(intArg1); //makes node
                nodeList.findNode(intArg1)->getHead()->insertR(stringArg, resistance, intArg1, intArg2); //inserts into nodes
                nodeList.findNode(intArg2)->getHead()->insertR(stringArg, resistance, intArg1, intArg2);
                cout << "Inserted: resistor " << stringArg << " " << setprecision(2) << resistance << " Ohms " << intArg1 << " -> " << intArg2 << endl;
            }
            else if (nodeList.nodeExists(intArg1) == true && nodeList.nodeExists(intArg2) == false){ //same as above
                nodeList.insertNode(intArg2);
                nodeList.findNode(intArg1)->getHead()->insertR(stringArg, resistance, intArg1, intArg2);
                nodeList.findNode(intArg2)->getHead()->insertR(stringArg, resistance, intArg1, intArg2);
                cout << "Inserted: resistor " << stringArg << " " << setprecision(2) << resistance << " Ohms " << intArg1 << " -> " << intArg2 << endl;
            }
            else{ //if both nodes do not exist
                nodeList.insertNode(intArg1); //creates both nodes
                nodeList.insertNode(intArg2);
                nodeList.findNode(intArg1)->getHead()->insertR(stringArg, resistance, intArg1, intArg2); //and inserts
                nodeList.findNode(intArg2)->getHead()->insertR(stringArg, resistance, intArg1, intArg2);
                cout << "Inserted: resistor " << stringArg << " " << setprecision(2) << resistance << " Ohms " << intArg1 << " -> " << intArg2 << endl;
            }
        }

        else if (command == "modifyR"){
            userInput >> stringArg >> resistance;
            Node* cur = nodeList.getHead(); //pointer to front of list of nodes
            bool found = false;
            double tmpRes = 0; //needed when printing confirmation message

            while (cur != NULL){
                if (cur->findRes(stringArg) == true){ //finds needed resistor in current node
                    found = true;
                    tmpRes = cur->getHead()->findResPoint(stringArg)->getResistance(); //gets resistance from needed resistor
                    cur->modifyRes(stringArg, resistance);
                }
                cur = cur->getNext();
            }
            if (found == true){
                cout << "Modified: resistor " << stringArg << " from "  << tmpRes << " Ohms to " << setprecision(2) << resistance << " Ohms" << endl;
            }
            else
                cout << "Error: resistor " << stringArg << " not found" << endl;
        }

        else if (command == "printR"){
            userInput >> stringArg;
            bool found = false;
            Node* cur = nodeList.getHead();
            while (cur != NULL){
                if (cur->findRes(stringArg) == true){ //finds needed resistor in current node
                    found = true;
                }
                cur = cur->getNext();
            }
            if (found == true)
                nodeList.printR(stringArg);
            else
                cout << "Error: resistor " << stringArg << " not found" << endl;
        }

        else if (command == "printNode"){
            userInput >> stringArg;
            Node* cur = nodeList.getHead();
            cout << "Print:" << endl;
            if (stringArg == "all"){
                while (cur != NULL){
                    if (cur->getHead()->getHead() != NULL){ //checks for empty head, therefore no resistors connected
                        cur->printNode();
                    }
                    cur = cur->getNext();
                }
            }
            else{
                stringstream tmp; //converts string to int
                int x;
                tmp << stringArg;
                tmp >> x;
                while (cur != NULL){
                    if (cur->getHead() != NULL && cur->getNodeNum() == x){ //checks if current node's number matches requested node's number
                        cur->printNode();
                    }
                    cur = cur->getNext();
                }
            }
        }

        else if (command == "deleteR"){
            userInput >> stringArg;
            Node* cur = nodeList.getHead();
            if (stringArg == "all"){
                while (cur != NULL){
                    cur->deleteResAll();
                    cur = cur->getNext();
                }
                cout << "Deleted: all resistors" << endl;
            }
            else{
                bool found = false;
                while (cur != NULL){
                    if (cur->findRes(stringArg) == true){ //checks if resistor is in current node
                        found = true;
                        cur->deleteR(stringArg);
                    }
                cur = cur->getNext();
                }
                if (found == true)
                    cout << "Deleted: resistor " << stringArg << endl;
                else
                    cout << "Error: resistor " << stringArg << " not found" << endl;
            }
        }

        else if (command == "setV"){
            userInput >> intArg1 >> voltage;
            if (nodeList.nodeExists(intArg1) == false){ //if node does not exist, create node and set voltage
                nodeList.insertNode(intArg1);
                nodeList.findNode(intArg1)->setVoltage(voltage);
            }
            else{
                Node* cur = nodeList.getHead();
                while (cur != NULL){
                    if (cur->getNodeNum() == intArg1) //checks to make sure node number is as requested
                        cur->setVoltage(voltage);
                    cur = cur->getNext();
                }
            }
            cout << "Set: node " << intArg1 << " to " << setprecision(2) << voltage << " Volts" << endl;
        }

        else if (command == "unsetV"){
            userInput >> intArg1;
            if (nodeList.nodeExists(intArg1) == false){
                nodeList.insertNode(intArg1);
            }
            else{
                Node* cur = nodeList.getHead();
                while (cur != NULL){
                    if (cur->getNodeNum() == intArg1)
                        cur->unsetVoltage();
                    cur = cur->getNext();
                }
            }
            cout << "Unset: the solver will determine the voltage of node " << intArg1 << endl;
        }

        else if (command == "solve"){
            bool oneSet = false;
            Node* cur = nodeList.getHead();
            while (cur != NULL){ //checks to make sure that at least 1 node's voltage is set
                if (cur->getSet() == true){
                    oneSet = true;
                }
                cur = cur->getNext();
            }
            if (oneSet == true){
                bool doneIteration = false; //flag for completely solving. ie all node's changes are less than MIN_ITERATION_CHANGE
                bool smallChange = false; //flag for if the change of an individual node is less than MIN_ITERATION_CHANGE
                while (doneIteration == false){
                    cur = nodeList.getHead(); //sets pointer to front of list of nodes so that it can go through all of them
                    while (cur != NULL){
                        if (cur->getSet() == false && cur->getHead()->getHead() != NULL){ //checks to see if the voltage is changeable (ie not set voltage)
                            double term1 = 0; //first part of voltage equation
                            double term2 = 0; //second part of voltage equation
                            double oldV = cur->getV();
                            term1 = cur->getHead()->makeFirstTerm();
                            Resistor* curRes = cur->getHead()->getHead(); //pointer to list of resistors in current node
                            while (curRes != NULL){
                                int neededNode; //node number of the other node that the resistor is connected to; opposite of current node
                                if (curRes->getEndpoint1() == cur->getNodeNum()) //if the resistor's first endpoint is the same as the current node
                                    neededNode = curRes->getEndpoint2(); //sets to node number of opposite node so that one can reference it when finding voltage
                                else //vice versa of above
                                    neededNode = curRes->getEndpoint1();
                                term2 += (nodeList.findNode(neededNode)->getV())/(curRes->getResistance()); //gets voltage of resistor's other node and divides by resistance
                                curRes = curRes->getNext(); //checks next resistor
                            }
                            cur->changeVoltage(term1*term2); //changes node voltage according to equation
                            if (abs(oldV-(term1*term2)) <= MIN_ITERATION_CHANGE) //checks if change to node is less than MIN_ITERATION_CHANGE
                                smallChange = true;
                            else
                                smallChange = false;
                        }
                        cur = cur->getNext();
                    }
                    if (smallChange == true) //this is only true if all nodes have been checked and smallChange is still true
                        doneIteration = true;
                }
                cout << "Solve:" << endl;
                cur = nodeList.getHead();
                while (cur != NULL){
                    if (cur->getHead() != NULL)
                        cout << "  Node " << cur->getNodeNum() << ": " << cur->getV() << " V" << endl;
                    cur = cur->getNext();
                }
            }
            else
                cout << "Error: no nodes have their voltage set" << endl;
        }

        userInput.clear(); //clears and ignores rest of stringstream
        userInput.ignore(1000,'\n');
    }
    Node* cur = nodeList.getHead();
    while (cur != NULL){ //goes through every node and deletes all resistors attached to it
        cur->deleteResAll();
        cur = cur->getNext();
    }
    cur = nodeList.getHead();
    Node* prev;
    while (cur != NULL){ //deletes all nodes
        prev = cur;
        cur = cur->getNext();
        delete prev;
    }
    return 0;
}
