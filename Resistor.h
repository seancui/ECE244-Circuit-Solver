//this file contains class definition and function declarations for Resistor class

#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>

using namespace std;

class Resistor
{
private:
   double resistance; // resistance (in Ohms)
   string name; // C++ string holding the label
   int endpointNodeIDs[2]; // IDs of nodes it attaches to
   Resistor *next;

public:
    Resistor(string nameArg, double _resistance, int endPoint1, int endPoint2, Resistor *nextRes);

   ~Resistor();

   string getName() const; // returns the name
   double getResistance() const; // returns the resistance

   int getEndpoint1() const;

   int getEndpoint2() const;

   void setResistance (double resistance_);

   void setEndpoints(int endpoint1, int endpoint2);

   void setName(string name);

   Resistor *getNext();

   void setNext(Resistor *next_);

   void print ();
};

ostream& operator<<(ostream&,const Resistor&);

#endif

