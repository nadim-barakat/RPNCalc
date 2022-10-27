/*
 * parser.cpp 
 * Nadim Barakat
 * 3/4/2022
 * CS 15 Proj 2 
 * 
 * This file contains the function called ParseRString. 
 * This function takes in a string that already had began with 
 * a {  then formats it into an RString. The RString has a 
 * format of { } where any operations that go into the RPNCalc 
 * can be in between the brackets. The function keeps 
 * track of the brackets to and keeps 
 * taking input until the brackets are balanced. 
 */


#include <fstream>
#include <iomanip> 
#include <iostream> 
#include <stdlib.h>
using namespace std; 


/* Name: parseRString(std::istream &input)
 * Purpose: creates an rString based on user input
 * RString is of format { } 
 * Parameters: an istream (file or cin practically)
 * Returns: the RString
 * Effects: removes trailing whitespace. checks balancing of 
 * parenthesis
 */
std::string parseRString(std::istream &input)
{
    std::string final_string = ""; 
    int opening_paren = 1; 
    int closing_paren = 0; 

    final_string += "{ "; 
    
    string curr; 

    while ((opening_paren - closing_paren > 0) and input >> curr)
    {
        if (curr == "{")
        {
            final_string += "{ "; 
            opening_paren++; 
        }
        else if (curr == "}")
        {
            final_string += "} ";  
            closing_paren++; 
        }
        else
        {
            final_string += curr; 
            final_string += " "; 
        }
    }
    final_string.pop_back();
    return final_string;
}
