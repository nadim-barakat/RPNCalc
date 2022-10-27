/*
 * RPNCalc.cpp 
 * Nadim Barakat
 * 3/4/2022
 * CS 15 Proj 2 
 * 
 * The RPNCalc.cpp implementation file allows for instantiation 
 * of the Reverse Polish Notation Calculator. By making an instance 
 * of this class with no parameters, the user can call the run 
 * function and have a functional RPN calculator. This will allow
 * them to pass their computations through the command line 
 * argument or through files. 
 * 
 * This class relies on the DatumStack class which is used 
 * in the heart of this class for calculator functionality. 
 * It also uses the Datum class as that is how data is represented.
 * 
 * The user should note that when bad input is given such as 
 * trying to call an operation when no numbers are on the stack, 
 * then the program will not crash. Instead, it will alert you
 * to the error and continue to accept input until "quit" is given 
 * or the program reaches EOF. 
 * 
 * User, I hope you enjoy the calculator!
 */


#include "DatumStack.h"
#include "Datum.h"
using namespace std; 
#include <fstream>
#include <iomanip> 
#include <iostream> 
#include "RPNCalc.h"



/* Name: RPNCalc()
 * Purpose: Makes an instance of RPNCalc. Default constructor 
 * Parameters: none
 * Returns: none
 * Effects: makes the RPNCalc object which can be used 
 *  to run the RPN calculator by user. 
 */
RPNCalc::RPNCalc()
{

}

/* Name: ~RPNCalc()
 * Purpose: Default destructor  
 * Parameters: none
 * Returns: none
 * Effects: clears any heap allocated memory
 * note: nothing is written here bc that is taken care of
 * by the std::list.  
 */
RPNCalc::~RPNCalc()
{
    
}

/* Name: run
 * Purpose: user calls this function to start the calculator 
 * Parameters: none
 * Returns: none
 * Effects: starts calculator. prints final message when done  
 */
void RPNCalc::run()
{
    cmd_loop(cin); 
    quit(); 

}

/* Name: cmd_loop(std::istream &cmd)
 * Purpose: main function that handles user input and calls
    appropriate helper functions. 
 * Parameters: an istream ( file or cin practically)
 * Returns: none
 * Effects: takes user input, makes appropriate calls based on input 
 */
void RPNCalc::cmd_loop(std::istream &cmd)
{
    string input;
    int int_value; 

    while (not is_finished and cmd >> input)
    {
        try
        {

            if (input == "quit")
            {
                is_finished = true; 
                return; 
            }
            else if (input == "print")
            {
                print(); 
            }
            else if (input == "#t" or input == "#f")
            {
                add_bool(input); 
            }
            else if (input == "not")
            {
                add_not();  
            }
            else if (got_int(input, &int_value))
            {
                add_int(int_value); 
            }
            else if (input == "clear")
            {
                datum_stack.clear(); 
            }
            else if (input == "drop")
            {
                datum_stack.pop(); 
            }
            else if (input == "dup")
            {
                duplicate(); 
            }
            else if (input == "swap")
            {
                swap(); 
            }
            else if (input == "+" or input == "-"
                 or input == "/" or input == "mod" or input == "*")
                 {
                    use_operator(input, "arith"); 
                 }
            else if (input == "<" or input == ">" or input == "<="
                or input == ">=")
                {
                    use_operator(input, "compare"); 
                }
            else if (input == "==") //needs own case. handled separate
            {
                use_operator(input, "equals"); 
            }
            else if (input == "{" )
            { 
                parse_and_add_to_stack(cmd); 
            }
            else if (input == "exec")
            {
                exec(); 
            }
            else if (input == "file")
            {
                file(); 
            }
            else if (input == "if")
            {
                if_cmd(); 
            }
            else 
            {
                cerr << input << ": unimplemented\n";
            }
        }
        catch (exception &e) //catch any error type thrown in program. 
        {
            cerr << "Error: " << e.what() << endl;
        }
    
    }
    
}

/* Name: add_int(int int_value)
 * Purpose: takes an integer, converts it to a datum
    and adds it to the stack. 
 * Parameters: an integer to be added. 
 * Returns: none
 * Effects: adds a number to stack after user wants to put in 
 * an integer to calculator. 
 */
void RPNCalc::add_int(int int_value)
{
    Datum int_datum(int_value); 
    datum_stack.push(int_datum);
}


/* Name: quit()
 * Purpose: prints final ouptut message when called
 * Parameters: none 
 * Returns: none
 * Effects: changes flag to true meaning user is done
 */
void RPNCalc::quit()
{
    is_finished = true; 
    cerr << "Thank you for using CalcYouLater.\n"; 
}

/* Name: print()
 * Purpose: prints top datum on stack 
 * Parameters: none 
 * Returns: none
 * Effects: throws error if stack is empty 
 */
void RPNCalc::print()
{
    cout << datum_stack.top().toString() << endl; 
}

/* Name: add_bool(string input)
 * Purpose: adds a true or false bool to stack depending on input
 * Parameters: the string that the user inputs (either #t or #f) 
 * Returns: none
 * Effects: adds a boolean to stack 
 */
void RPNCalc::add_bool(string input)
{

    if (input == "#t")
    {
        Datum bool_datum(true);
        datum_stack.push(bool_datum); 
    }
    else // false case 
    {
        Datum bool_datum(false);
        datum_stack.push(bool_datum); 
    }
}

/* Name: add_not()
 * Purpose: flips the value of the boolean on the stack 
    ex: #f to #t 
 * Parameters: none
 * Returns: none
 * Effects: if top element is not a bool, it throws an error  
 */
void RPNCalc::add_not()
{

    Datum top_datum(get_top_then_pop()); 
    bool top_bool = top_datum.getBool(); 

    Datum new_datum(not top_bool); 
    datum_stack.push(new_datum); 
}

/* Name: get_top_then_pop()
 * Purpose: gets the top Datum on the stack then pops it off
 * Parameters: none
 * Returns: the top datum on stack if possible 
 * Effects: throws error if stack is empty 
 */
Datum RPNCalc::get_top_then_pop()
{
    Datum top_datum(datum_stack.top()); 
    datum_stack.pop(); 

    return top_datum; 
}

/* Name: got_int(string s, int *resultp)
 * Purpose: checks if string is a integer or not
 * Parameters: a string to check. an integer to hold the 
 * value of the result 
 * Returns: true if string can be an integer. false otherwise 
 * Effects: credit to Mark Sheldon 
 */
bool RPNCalc::got_int(string s, int *resultp)
{
    /* Holds the first non-whitespace character after the integer */
    char extra;
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/* Name: duplicate()
 * Purpose: duplicates the top element on the stack 
 * Parameters: none
 * Returns: none
 * Effects: puts duplicated datum onto stack 
 */
void RPNCalc::duplicate()
{
    Datum new_datum(datum_stack.top());
    datum_stack.push(new_datum); 
}

/* Name: swap()
 * Purpose: switches top datum with one below it  
 * Parameters: none
 * Returns: none
 * Effects: removes top two elements then puts them back in 
 * reverse order 
 */
void RPNCalc::swap()
{
    Datum new_bottom(get_top_then_pop()); 
    Datum new_top(get_top_then_pop()); 
    //get top two 

    //add in reverse
    datum_stack.push(new_bottom); 
    datum_stack.push(new_top); 
}

/* Name: use_operator(string input, string cmd)
 * Purpose: handles all operations such as compairsons, equality or
  arithmetic by calling helper functions 
 * Parameters: the user's input, and a cmd based on what type 
 * of operation was called 
 * Returns: none
 * Effects: calls helper function to carry out math expression
 */
void RPNCalc::use_operator(string input, string cmd)
{
    Datum top_datum(get_top_then_pop()); 
    Datum bottom_datum(get_top_then_pop());

    if (cmd == "arith") //like + - 
    {
        compute_operator(bottom_datum.getInt(), top_datum.getInt(), input);
    } 
    else if (cmd == "compare") //like  > 
    {
        compare_operator(bottom_datum.getInt(), top_datum.getInt(), input);
    }
    else if (cmd == "equals")
    {
        compare_equals(bottom_datum.toString(), top_datum.toString()); 
    }
}

/* Name: compare_equals(string bottom, string top)
 * Purpose: compares the value of the bottom datum 
 * with that of the top datum for equality  
 * Parameters: the strings of the top and bottom datums 
 * Returns: none
 * Effects: puts boolean from comparison on the stack 
 */
void RPNCalc::compare_equals(string bottom, string top)
{
    bool result = (bottom == top); 
    Datum new_datum(result); 
    datum_stack.push(new_datum);
}

/* Name: compare_operator(int bottom, int top, string oper)
 * Purpose: carries out comparisons of two datum's integers 
 * then pushes result boolean on stack 
 * Parameters: the integer of the top and bottom datums. 
 * the operation like < that the user inputs 
 * Returns: none
 * Effects: puts boolean from comparison on the stack 
 */
void RPNCalc::compare_operator(int bottom, int top, string oper)
{
    bool result = false; 

    if (oper == "<")
    {
        result = bottom < top; 
    }
    else if (oper == ">")
    {
        result = bottom > top; 
    }
    else if (oper == "<=")
    {
        result = bottom <= top; 
    }
    else if (oper == ">=")
    {
        result = bottom >= top; 
    }
    else if (oper == "==")
    {
        result = bottom == top; 
    }

    Datum new_datum(result); 
    datum_stack.push(new_datum); 
}

/* Name: compute_operator(int bottom, int top, string oper)
 * Purpose: carries out arthmitic of two datum's integers 
 * then pushes result boolean on stack 
 * Parameters: the integer of the top and bottom datums. 
 * the operation like + that the user inputs 
 * Returns: none
 * Effects: makes sure division or mod 0 throws error. 
 */
void RPNCalc::compute_operator(int bottom, int top, string oper)
{
    int result = 0; 

    if (oper == "+")
    {
        result = bottom + top; 
    }
    else if (oper == "-")
    {
        result = bottom - top; 
    }
    else if (oper == "*")
    {
        result = bottom * top; 
    }
    else if (oper == "/")
    {
        divide_by_zero_error(top); 
        result = bottom / top;
    }
    else if (oper == "mod")
    {
        divide_by_zero_error(top); 
        result = bottom % top; 
    } 

    Datum new_datum(result); 
    datum_stack.push(new_datum); 
}


/* Name: divide_by_zero_error(int top)
 * Purpose: throws error if about to divide by zero 
 * Parameters: the integer of top datum 
 * Returns: none
 * Effects: throws error if attempt to divide by 0
 */
void RPNCalc::divide_by_zero_error(int top)
{
    if (top == 0)
    {
        throw invalid_argument("division by 0.");
    }
}

/* Name: parse_and_add_to_stack(std::istream &input)
 * Purpose: Parses an RString then pushes the parsed string onto 
 * the stack. 
 * Parameters: an istream (file or cin practically)
 * Returns: none
 * Effects: pushes the parsed string onto stack 
 */
void RPNCalc::parse_and_add_to_stack(std::istream &input)
{
    string parsed_output = parseRString(input); 
    Datum new_datum(parsed_output); 
    datum_stack.push(new_datum); 
}

/* Name: parseRString(std::istream &input)
 * Purpose: creates an rString based on user input
 * RString is of format { } 
 * Parameters: an istream (file or cin practically)
 * Returns: the RString
 * Effects: removes trailing whitespace. checks balancing of 
 * parenthesis
 */
std::string RPNCalc::parseRString(std::istream &input)
{
    std::string final_string = ""; 
    int opening_paren = 1; 
    int closing_paren = 0; 

    final_string += "{ "; 
    
    string curr; 

    //condition to check that parens are balanced
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
    final_string.pop_back(); //remove trailing whitespace 
    return final_string;
}

/* Name: get_and_check_RString(string error_message)
 * Purpose: gets top Datum, pops it, then checks if it is an RString
 * to be used in exec() function 
 * Parameters: an error message to be thrown if type is not RString 
 * Returns: the RString datum on top of stack 
 * Effects: pops of top datum always 
 */
Datum RPNCalc::get_and_check_RString(string error_message)
{

    Datum top_datum(get_top_then_pop());

    if (not top_datum.isRString())
    {
        throw std::logic_error(error_message);
    }
    return top_datum; 
}

/* Name: exec()
 * Purpose: executes commands inside RString using command loop 
 * Parameters: none
 * Returns: none
 * Effects: can handle nested commands
 */
void RPNCalc::exec()
{

    Datum top_datum(get_and_check_RString("cannot execute non rstring")); 

    //1 command because only remove paren and not extra whitespace
    string clean_string = clean_RString(1, top_datum.getRString());

    istringstream iss(clean_string); 

    cmd_loop(iss); 

}

/* Name: clean_RString(int value, string string_datum)
 * Purpose: Removes front and last parenthesis of RString. 
 * if called on file, also removes whitespace 
 * Parameters: a value (1 for exec and 2 for file ). 1 to remove only
 * parenthesis or 2 to remove whitespace
 * Returns: none
 * Effects: can handle exec and file commands 
 */
string RPNCalc::clean_RString(int value, string string_datum)
{
    string_datum.erase(0, value); //remove paren or paren+whitespace
    //file cmd removes whitespace 

    string_datum.pop_back(); //always remove last paren 

    if (value == 2)
    {
        string_datum.pop_back(); //needed by file cmd 
        // removes trailing whietspace  
    }
    return string_datum; 
}

/* Name: file()
 * Purpose: gets the filename then calls function to open file   
 * Parameters:none
 * Returns: none
 * Effects: opens file by filename from user RString  
 */
void RPNCalc::file()
{
    Datum top_datum(get_and_check_RString("file operand not rstring"));

    // 2 cmd to remove whitespace 
    string filename = clean_RString(2, top_datum.getRString());

    open_file(filename);


}

/* Name: open_file(string filename)
 * Purpose: opens the file if possible.  
 * Parameters: the filename to open 
 * Returns: none
 * Effects: throws error if opening file not possible 
 */
void RPNCalc::open_file(string filename)
{
    ifstream my_file; 
    my_file.open(filename); 

    if (not my_file.is_open()) // bad file 
    {
        cerr << "Unable to read " << filename << endl; 
        return; 
    }

    cmd_loop(my_file); 

    my_file.close(); //don't forget to close!


}

/* Name: if_cmd()
 * Purpose: gets top three datums 
    executes false case if boolean on stack is false
    executes true case if boolean on stack is true 
 * Parameters: none
 * Returns: none
 * Effects: throws error if empty stack or if Datums are wrong type
 */
void RPNCalc::if_cmd()
{
    Datum false_case(get_top_then_pop()); // will throw error if empty
    Datum true_case(get_top_then_pop()); 

    Datum if_bool(get_top_then_pop()); 

    if (not type_check_if_cmd(if_bool.isBool(), 
        false_case.isRString(), true_case.isRString()))
    {
        return; //throws error if wrong type 
    }

    if (if_bool.getBool())
    {
        datum_stack.push(true_case); 
    }
    else 
    {
        datum_stack.push(false_case); 
    }
    exec(); 
}

/* Name: type_check_if_cmd(bool if_bool, bool false_case, bool true_case)
 * Purpose: makes sure the datums are of the correct type 
 * before calling the if command 
 * Parameters: use the isType() functions from Datum. 
 *      the boolean value on whether the first value is a bool 
 *      the boolean value on whether the next two datums are Rstrings
 * Returns: true if everything is right type. False if something 
 *      is wrong type 
 * Effects: checks the boolean value first. Does not look at theRStrings 
 *      if first boolean is wrong type
 */
bool RPNCalc::type_check_if_cmd(bool if_bool, bool false_case, bool true_case)
{

    if (not if_bool)
    {
        cerr << "Error: expected boolean in if test\n"; 
        return false; 
    }
    if (not false_case or not true_case)
    {
        cerr << "Error: expected rstring in if branch\n"; 
        return false; 
    }
    return true;
}