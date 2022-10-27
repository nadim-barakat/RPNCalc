/*
 * main.cpp 
 * Nadim Barakat
 * 3/4/2022
 * CS 15 Proj 2 
 * 
 * In this file, 
 * The main.cpp allows the user to start 
 * the Reverse Polish Notation Calculator. By launching this main, 
 * the calcultor will launch in the terminal. The user can input 
 * their inputs directly and see the outputs from the computations. 
 * The user can also pass in files and the computation will also 
 * acts on those inputs. 
 * 
 * This main.cpp uses the RPNCalc class. The calculator is called
 * by making an instance of the RPNCalc then calling the 
 * run function. That is all the user needs to know in terms of 
 * implementation to launch and use the program. 
 */


#include "DatumStack.h"
#include "Datum.h"
#include <iostream>
#include <fstream>
using namespace std; 
#include "RPNCalc.h"

int main()
{
 
    RPNCalc my_calc;
    my_calc.run(); //this is all the user needs to run the calc
    
    return 0; 
}








