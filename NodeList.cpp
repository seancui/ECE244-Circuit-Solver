//this file contains function definitions for NodeList class

#include "NodeList.h"
#include <iomanip>

NodeList::NodeList(){
    nodeHead = NULL;
}

void NodeList::insertNode(int nodeNum_){
    Node* cur = nodeHead;
    Node* prev;
    if(cur == NULL){ //if there are no nodes in list
        Node* node = new Node(nodeNum_, NULL);
        nodeHead = node;
    }
    else{
        bool break1 = false;
        bool break2 = false;
        while(cur != NULL){
            if (cur->getNodeNum() > nodeNum_){ //if the node to insert's number is smaller than the head node's number
                break1 = true;
                break; //stop loop to prevent checking other nodes and prevent checking second case
            }
            if (cur->getNext() != NULL){
                if(cur->getNext()->getNodeNum() > nodeNum_){ //if the next node's number is greater than node to insert's number, cur is in the right spot and should insert between current and next node
                    break2 = true;
                    break;
                }
            }
            prev = cur;
            cur = cur->getNext();
        }
        if (cur == nodeHead && break1 == true && break2 == false){ //insert to front of list
            Node* node = new Node(nodeNum_, cur);
            nodeHead = node;
        }
        else if (break1 == false && break2 == true){ //insert in middle of list
            Node* node = new Node(nodeNum_, cur->getNext());
            cur->setNext(node);
        }
        else if (cur == NULL){ //insert to end of list
            Node* node = new Node(nodeNum_, NULL);
            prev->setNext(node);
        }
    }
}

bool NodeList::nodeExists(int nodeNum){
    Node* cur = nodeHead;
    while(cur != NULL){
        if (nodeNum == cur->getNodeNum())
            return true;
        cur = cur->getNext();
    }
    return false; //otherwise node number not found
}

Node* NodeList::findNode(int nodeNum){
    Node* cur = nodeHead;
    while(cur != NULL){
        if (nodeNum == cur->getNodeNum()){
            return cur;
        }
        cur = cur->getNext();
    }
}

Node* NodeList::getHead(){
    return nodeHead;
}
void NodeList::printR(string name){
    Node* cur = nodeHead;
    while (cur != NULL){
        cur->printRes(name);
        if (cur->getHead()->findR(name) == true)
            return; //if the resistor is found in current node return to prevent checking other nodes to prevent printing twice
        cur = cur->getNext();
    }
}

int NodeList::getSize(){
    int size = 0;
    Node* cur = nodeHead;
    while (cur != NULL){
        size += 1;
        cur = cur->getNext();
    }
    return size;
}
