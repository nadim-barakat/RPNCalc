/*
 * RPNCalc.h 
 * Nadim Barakat
 * 3/4/2022
 * CS 15 Proj 2 
 * 
 * The RPNCalc Class acts as the functional Reverse Poliish Notion Calculator
 * (RPN). It This allows the user to put operations into the calculator 
 * and get the computed output. The user has certain commands they can 
 * use on this class such as printing the top most Datum or dropping
 * the top most Datum. 
 * This class also supports input from the command line or from files. 
 * 
 * The constructor creates an empty calculator and the user can begin 
 * the calculator by just calling the run function. 
 */


#ifndef _RPNCALC_H_
#define _RPNCALC_H_


#include <iostream>
#include <fstream>
#include "Datum.h"
#include <list>
#include "DatumStack.h"
using namespace std; 

class RPNCalc
{
public:
  
    RPNCalc(); 
    ~RPNCalc(); 
    void run(); 
    //run is the only function the user needs to 
    //start the calculator. 


private:

    DatumStack datum_stack; 
    bool is_finished = false; 

    void quit(); 
    void print(); 
    void add_bool(string input); 
    void add_not(); 
    bool got_int(string s, int *resultp); 
    void add_int(int int_value); 
    void drop(); 
    void duplicate(); 
    void divide_by_zero_error(int top); 
    void swap(); 
    Datum get_top_then_pop(); 
    void use_operator(string input, string cmd); 
    void compute_operator(int bottom, int top, string oper); 
    void compare_operator(int bottom, int top, string oper); 
    void compare_equals(string bottom, string top); 
    std::string parseRString(std::istream &input); 
    void parse_and_add_to_stack(std::istream &input);
    void cmd_loop(std::istream &input);
    void exec(); 
    Datum get_and_check_RString(string error_message); 
    string clean_RString(int value, string string_datum);
    void open_file(string filename);
    void file();
    void if_cmd();  
    bool type_check_if_cmd(bool if_bool, bool false_case, bool true_case);
};

#endif
