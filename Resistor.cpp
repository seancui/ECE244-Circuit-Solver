//this file contains function definitions for Resistor class

#include "Resistor.h"
#include "Node.h"
#include <iomanip>

Resistor::Resistor(string nameArg, double _resistance, int endPoint1, int endPoint2, Resistor *nextRes){
    name = nameArg;
    resistance = _resistance;
    endpointNodeIDs[0] = endPoint1;
    endpointNodeIDs[1] = endPoint2;
    next = nextRes;
}

Resistor::~Resistor()
{
}

string Resistor::getName() const{
    return name;
}

double Resistor::getResistance() const{
    return resistance;
}

int Resistor::getEndpoint1() const{
    return endpointNodeIDs[0];
}
int Resistor::getEndpoint2() const{
    return endpointNodeIDs[1];
}

void Resistor::setResistance(double resistance_){
    resistance = resistance_;
}

void Resistor::setEndpoints(int endpoint1, int endpoint2){
    endpointNodeIDs[0] = endpoint1;
    endpointNodeIDs[1] = endpoint2;
}

void Resistor::setName(string name1){
    name = name1;
}

Resistor* Resistor::getNext(){
    return next;
}

void Resistor::setNext(Resistor *next_){
    next = next_;
}

void Resistor::print(){
    cout << left << setw(20) << name << right << setw(8) << setprecision(2) << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
 }

