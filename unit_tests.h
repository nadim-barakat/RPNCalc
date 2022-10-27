/*
 * unit.tests.h  
 * Nadim Barakat
 * 3/4/2022
 * CS 15 Proj 2 
 * 
 * The unit_tests.h file tests the functions from week 1. 
 * The general startegy of this file is that it calls 
 * one of the new functions then useses the assert function
 * to assert that the result of using that function is the 
 * same as the expected outcome. 
 * 
 * This file tests both regular and edge cases to make 
 * sure that the functions work as expected. 
 */
#include <cassert>
using namespace std; 
#include <iostream> 
#include "DatumStack.h"
#include "Datum.h"
#include <sstream>
#include <fstream>
#include <iomanip> 
#include <iostream> 
#include <cassert>
#include "RPNCalc.h"


/* Name: test_empty_construct()
 * Purpose: creates a DatumStack instance
        and makes sure the size is 0
 * Parameters: none
 * Returns: none
 * Effects: also tests size function
 */
void test_empty_construct()
{
    DatumStack datum_stack; 
    assert(datum_stack.size() == 0); 
}

/* Name: test_DatumStack_push()
 * Purpose: adds two Datums and makes sure size is 2
 * Parameters: none
 * Returns: none
 * Effects: adds different types of datums
 */
void test_DatumStack_push()
{
    Datum datum1(3); 
    Datum datum2(true);

    DatumStack datum_stack; 
    datum_stack.push(datum1); 
    datum_stack.push(datum2);

    assert(datum_stack.size() == 2); 
}

/* Name: test_DatumStack_size()
 * Purpose: adds 50 datums to stack. checks size 
 * Parameters: none
 * Returns: none
 * Effects: uses loop to add to stack
 */
void test_DatumStack_size()
{
    Datum datum1(3); 

    DatumStack datum_stack; 

    for (int i = 0; i < 50; i++)
    {
        Datum datum1(3);
        datum_stack.push(datum1); 
    }

    assert(datum_stack.size() == 50); 

}

/* Name: test_clear_empty_list()
 * Purpose: makes sure clear works if stack
    is empty 
 * Parameters: none
 * Returns: none
 * Effects: tests empty stack 
 */
void test_clear_empty_list()
{
    DatumStack datum_stack; 

    datum_stack.clear(); 
    assert(datum_stack.size() == 0); 
}

/* Name: test_clear_full_list()
 * Purpose: adds to stack then clears. Makes sure size is empty 
 * Parameters: none
 * Returns: none
 * Effects: adds different datum types  
 */
void test_clear_full_list()
{
    DatumStack datum_stack; 

    Datum datum1(3); 
    Datum datum2("hello");
    Datum datum3(false);
    Datum datum4(&datum1);

    datum_stack.push(datum1); 
    datum_stack.push(datum3);
    datum_stack.push(datum2);
    datum_stack.push(datum4);

    datum_stack.clear(); 
    assert(datum_stack.size() == 0); 
}

/* Name: test_top_empty_error()
 * Purpose: tries getting top of empty stack. 
    checks that error is thrown and it matches expected msg 
 * Parameters: none
 * Returns: none
 * Effects: catches error 
 */
void test_top_empty_error()
{
    DatumStack datum_stack; 
    bool runtime_error_thrown = false; 
    std::string error_message;

    try
    {
        Datum datum_1 = datum_stack.top();
    } 
    catch(std::runtime_error &e)
    {
        error_message = e.what(); 
        runtime_error_thrown = true; 
    }

    assert(runtime_error_thrown); 
    assert(error_message == "empty_stack");

}

/* Name: test_top_full_list()
 * Purpose: gets top of a populated list 
 * Parameters: none
 * Returns: none
 * Effects: asserts top msg is expected datum string 
 */
void test_top_full_list()
{

    DatumStack datum_stack; 

    Datum datum1(3); 
    Datum datum2("hello");
    Datum datum3(false);
    Datum datum4(true);

    datum_stack.push(datum1); 
    datum_stack.push(datum2);
    datum_stack.push(datum3);
    datum_stack.push(datum4);

    Datum top_datum = datum_stack.top(); 
    assert(top_datum.toString() == "#t");
}

/* Name: test_pop_full()
 * Purpose: fills stack then pops off an element. Makes 
    sure size is one less 
 * Parameters: none
 * Returns: none
 * Effects: checks both size of stack 
 *  and string value of new top  
 */
void test_pop_full()
{
    DatumStack datum_stack; 

    Datum datum1(3); 
    Datum datum2("hello");
    Datum datum3(false);
    Datum datum4(true);

    datum_stack.push(datum1); 
    datum_stack.push(datum2);
    datum_stack.push(datum3);
    datum_stack.push(datum4);

    datum_stack.pop(); 
    assert(datum_stack.size() == 3); 

    assert(datum_stack.top().toString() == "#f");

}

/* Name: test_pop_empty_error()
 * Purpose: pops from an empty stacks. Makes sure 
    error is thrown with right message 
 * Parameters: none
 * Returns: none
 * Effects: catches thrown error   
 */
void test_pop_empty_error()
{
    DatumStack datum_stack; 
    bool runtime_error_thrown = false; 
    std::string error_message;

    try
    {
        datum_stack.pop();
    } 
    catch(std::runtime_error &e)
    {
        error_message = e.what(); 
        runtime_error_thrown = true; 
    }

    assert(runtime_error_thrown); 
    assert(error_message == "empty_stack");
}

/* Name: test_array_constructor()
 * Purpose: uses array of Datum to initialize a new stack 
 * Parameters: none
 * Returns: none
 * Effects: asserts size is same as that from array 
 *  asserts using top that datums added in correct order 
 */
void test_array_constructor()
{
    Datum data[2] = {Datum(5), Datum(true)};

    DatumStack d(data, 2);

    assert(d.top().toString() == "#t"); 
    assert(d.size() == 2); 
}

//declaration from parser.cpp 
std::string parseRString(std::istream &input); 

/* Name: test_parseRString()
 * Purpose: tests making a simple Rstring with extra space 
 * Parameters: none
 * Returns: none
 * Effects: uses istringstream bc that is accepted input 
 */
void test_parseRString()
{
    string test_values_1 = " 1 2 + }"; 
    istringstream iss(test_values_1); 
    assert(parseRString(iss) == "{ 1 2 + }");  
}

/* Name: test_nested_parseRString()
 * Purpose: tests a nested Rstring with no leading space 
 * Parameters: none
 * Returns: none
 * Effects: asserts output is as expexcted 
 */
void test_nested_parseRString()
{
    string test_values_1 = "1 { 4 2 / } / }"; 
    istringstream iss(test_values_1); 
    assert(parseRString(iss) == "{ 1 { 4 2 / } / }"); 
}

/* Name: test_file_parser()
 * Purpose: tests file arguement and parsing the nested
    RString 
 * Parameters: none
 * Returns: none
 * Effects: takes input from file 
 */
void test_file_parser()
{
    ifstream my_file; 
    my_file.open("simple_test_parser.cylc"); 
    assert(parseRString(my_file) == "{ { 4 + } 7 / 9 }"); 
}

/* Name: test_diff_types_parseRString()
 * Purpose: tests more complicated nested with  
    words, bools, and ints 
 * Parameters: none
 * Returns: none
 * Effects: tests many types and many nested brackets 
 */
void test_diff_types_parseRString()
{
    string test_values_1 = "7 { 21 { print } / { #t } } / }"; 
    istringstream iss(test_values_1); 
    assert(parseRString(iss) == "{ 7 { 21 { print } / { #t } } / }");
}