/*
 * DatumStack.cpp
 * Nadim Barakat
 * 3/4/2022
 * CS 15 Proj 2 
 * 
 * The DatumStack.cpp implementation file gives functionality to the stack
 * of Datum objects. This allows for the addition of Datums into the stack,
 * their removal, and other functionalities that allow for interaction
 * with this stack of Datum Objects. 
 * The default consutructor takes no parameters and initializes 
 * the empty DatumStack. There is also another constructor which 
 * can be called with an array of Datums and that array's size. Both
 * allow for the creation of the DatumStack instance, however, the 
 * second constructor will preopulate the DatumStack with Datums 
 * from the array. 
 * 
 * Overall, this implementations produces a working stack of Datum objects
 * that will be heavily used in the RPNCalc class which makes 
 * a calculator using Reverse Polish Notation. 
 */

#include "DatumStack.h"
#include "Datum.h"
using namespace std; 
#include <fstream>
#include <iomanip> 
#include <iostream> 

/* DatumStack()
 * Purpose: Makes an instance of DatumStack. Default constructor 
 * Parameters: none
 * Returns: none
 * Effects: makes the DatumStack object which can be used 
 *  to hold Datum objects as a stack. 
 */
DatumStack::DatumStack()
{

}

/* Name: DatumStack(Datum array[], int index)
 * Purpose: Constructor that uses an array of Datums and that 
        arrays size to prepoulate the DatumStack. 
 * Parameters: array of Datums and that arrays size 
 * Returns: none
 * Effects: Makes a DatumStack that holds the Datums in the 
 * array. 
 */
DatumStack::DatumStack(Datum array[], int index)
{
    for (int i = 0; i < index; i++)
    {
        push(array[i]); 
    }
}

/* Name: DatumStack(Datum array[], int index)
 * Purpose: Constructor that uses an array of Datums and that 
        arrays size to prepoulate the DatumStack. 
 * Parameters: array of Datums and that arrays size 
 * Returns: none
 * Effects: Makes a DatumStack that holds the Datums in the 
 * array. 
 */
void DatumStack::push(Datum elem)
{
    datum_list.push_front(elem); 
}

/* Name: size()
 * Purpose: returns the size of the DatumStack 
 * Parameters: none 
 * Returns: an integer of the size of the DatumStack 
 * Effects: gets the size 
 */
int DatumStack::size()
{
    return datum_list.size(); 
}

/* Name: clear()
 * Purpose: empties the DatumStack 
 * Parameters: none 
 * Returns: none
 * Effects: size will be 0 after clear is called 
 */
void DatumStack::clear()
{
    datum_list.clear(); 
}

/* Name: top()
 * Purpose: gets the Datum at the top of the DatumStack 
 * Parameters: none
 * Returns: the Datum at the top of the stack 
 * Effects: does not remove the top Datum. 
 *  Throws an error if the stack is empty 
 */
Datum DatumStack::top()
{
    throw_error_if_empty(); 

    return datum_list.front(); 
}

/* Name: top()
 * Purpose: gets the Datum at the top of the DatumStack 
 * Parameters: none
 * Returns: the Datum at the top of the stack 
 * Effects: does not remove the top Datum. 
 *  Throws an error if the stack is empty 
 */
void DatumStack::throw_error_if_empty()
{
    if (isEmpty())
    {
        throw std::runtime_error("empty_stack"); 
    }
}

/* Name: pop()
 * Purpose: removes the top Datum from the DatumStack 
 * Parameters: none
 * Returns: none
 * Effects: removes the top Datum without returning it 
 *  Throws an error if the stack is empty 
 */
void DatumStack::pop()
{
    throw_error_if_empty(); 
    datum_list.pop_front(); 
}

/* Name: isEmpty()
 * Purpose: checks if the DatumStack is empty 
 * Parameters: none
 * Returns: true if empty, false otherwise 
 * Effects: uses previous size funct
 */
bool DatumStack::isEmpty()
{
    return (size() == 0);
}