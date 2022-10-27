/*
 * DatumStack.h 
 * Nadim Barakat
 * 3/4/2022
 * CS 15 Proj 2 
 *
 * The DatumStack Class acts like a stack for Datum objects. 
 * Datum objects are containers that can hold strings, bools, or integers.
 * The DatumStack class allows for storage of the Datum Objects and gives 
 * the user certain functionality like that of a stack. This DatumStack 
 * class will be used by the RPNCalc class which allows for the usage of 
 * a calculator in Reverse Polish Notation. 
 * 
 * Every DatumStack class starts with an empty stack and then it  
 * can be populated with Datum objects using the class's functions. 
 * Other functions include getting the top Datum or removing the top 
 * Datum. 
 */

#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_


#include <vector>
using namespace std; 
#include <iostream>
#include <fstream>
#include "Datum.h"
#include <list>

class DatumStack
{
public:
    void push(Datum elem); 
    int size(); 
    void clear(); 
    Datum top(); 
    bool isEmpty(); 
    void pop(); 
    DatumStack(Datum array[], int index); 
    DatumStack(); 

private:

    //linked list to represent the stack 
    std::list<Datum> datum_list; 

    void throw_error_if_empty();
};

#endif
