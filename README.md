/*
 * README
 * Nadim Barakat
 * 3/7/2022
 * CS 15 Proj 2 
 * 
 * This README file describes the purpose of this program, 
 * help recieved, how to compile, testing, and important data
 * structures  
 */


Author: Nadim Barakat 
Title: CalcYouLater, Project 2, CS 15 

Purpose: The purpose of this program was to build a reverse 
polish notation (RPN) calculator for our users. This 
calculator comes with many capabilites that will allow the 
user to pass in a variety of inputs which can be done manually 
or through a file. 

Help: 
I reveived help from many TAs. They are great and helped me 
through bugs and with bigger picture organinzation. 
some testing files used were from Mark Sheldon and Pippa Hodgkins.

I also used the following website to help with the data
structures section. 
https://levelup.gitconnected.com
the-stack-data-structure-what-is-it-and-how-is-
\it-used-in-javascript-23562fb8a590 

Provided Files: 

DatumStack.cpp: 
    The DatumStack.cpp implementation file gives functionality to the stack
    of Datum objects. This allows for the addition of Datums into the stack,
    their removal, and other functionalities that allow for interaction
    with this stack of Datum Objects.

DatumStack.h: 
    The DatumStack Class acts like a stack for Datum objects. 
    Datum objects are containers that can hold strings, bools, or integers.
    The DatumStack class allows for storage of the Datum Objects and gives 
    the user certain functionality like that of a stack.

main.cpp:
    The main.cpp allows the user to start 
    the Reverse Polish Notation Calculator. By launching this main, 
    the calcultor will launch in the terminal.

Makefile: 
    Compiles all files cpp and .h files. 
    The executable made is called CalcYouLater 

RPNCalc.cpp: 
    The RPNCalc.cpp implementation file allows for instantiation 
    of the Reverse Polish Notation Calculator. By making an instance 
    of this class with no parameters, the user can call the run 
    function and have a functional RPN calculator.

RPNCalc.h: 
    The RPNCalc Class acts as the functional Reverse
    Poliish Notion Calculator(RPN). 
    It This allows the user to put operations into the calculator 
    and get the computed output.

unit_tests.h: 
    tests DatumStack and parser.cpp functions from week 1. 
    uses assert to ensure correct output. tests normal and edge cases. 

parser.cpp: 
    This file contains the function called ParseRString. 
    This function takes in a string that already had began with 
    a {  then formats it into an RString.

test_operations.cyl: 
    this file tests the operations such as +, -, *, /, mod

test_file_that_calls_files.cyl: 
    This file tests the file command 
    It tests many of the previously created files 

test_compare.cyl: 
    this file tests the operations such as <, >, ==, <=, >=
    It also tests edge cases such as comparing Datums 
    that are not ints which should throw an error

simple_test_parser.cyl: 
    this file passes a nested incomplete Rstring 
    which can be used by the parser.cpp file 
    to created the RString 

if_tests.cyl: 
    tests both error and normal cases of the if command 

general_cmds.cyl: 
    This tests the general commands like add, swap, print, not. 

exec_test.cyl: 
    This file tests the exec function of the RPNCalc
    It tests nested and simple RStrings and error cases 

empty_file.cyl: 
    This is just an empty file to test the file cmds 

compilation and running: 
    the entire program can be compiled just by using the 
    command "make". 
    It can be run using ./CalcYouLater
    then the person can start using the calculator direclty 

Data structures 
Stacks are linear ADT data strucures that operate using something 
called LIFO. This means that the last element to enter the stack
is the first element to be taken out. In a stack, we are only 
dealing with the top most element. We can add or take away
from the top of the stack, but we can't access the middle 
parts of the stack or end. These operations are done using 
push and pop functions to add or take away from the top of 
the stack. The advantages of stacks is that they can be efficient.  
To explain, pushing and popping from the stack can be done 
in constant time or O(1) becuase we just access the top. We 
don't loop through all the elements and can easily access the top.
If a person needed to access the middle or end of their 
data structure, however, then a stack would not be an 
adequate way to solve their problem.  

In the RPNCalc, we were only ever dealing with the topmost element
on the stack. We always added things to the top and removed from
the top. We didn't need random access into the stack or to be able 
to access the end of the stack. This made it very useful for us
to use a stack in this program because we could then do all of our 
operations in O(1) time. 

After doing some research, I learned that "undo" buttons in 
editors can operate using stacks. This makes sense because
the current state can be saved on the top of the stack. When 
a person clicks "undo" the current state is popped off and 
the earlier state below it is now at the top. 
I also learned that stacks can be useful when backtracking in 
a maze. For example, if the computer is trying to solve a maze, 
it can save each move on the stack. Then when it needs to 
backtrack, it can pop each step off the stack and go backwards. 
This can help it take a new path and ultimately solve the maze. 

https://levelup.gitconnected.com
the-stack-data-structure-what-is-it-and-how-is-
\it-used-in-javascript-23562fb8a590


Testing: 
    week 1 testing: 
    My strategy for week 1 testing was to build each function
    then use the unittest framework to test the normal and 
    edge cases of that function. I first started by building 
    my constructor and creating a test to make sure it worked. 
    I the build the size function because I knew I would need it
    in my constructor test and other tests. I then asserted
    that my defualt constructor had a size of 0. 
    After I wrote push, I added a few datums to the stack and 
    checked the size. I also tried adding 50 datums using 
    a loop to make sure my stack could handle it. 
    When I built clear, I wanted to test it on the edge case
    of the empty stack. I did this and used my size function
    to assert that the size was still 0. 
    For top and pop, I needed to account for both the empty and 
    filled stacks. For the empty stack, I asserted
    that an error was thrown when they were called and that
    the message matched my exact output. I also made sure
    that pop decreased the size of the stacks when called. 
    For my other constructor, I made sure that it could 
    accept an array. To test whether things were being added
    in the correct order, I asserted that the top's string was 
    exactly the same as the last one placed. I was also 
    wary of Datums of different types so I added Datums using 
    this array constuctor of different types (ex: bool and Rstring).
    For my parser.cpp function, I tested using both file inputs 
    and regular inputs. I made test cases for RStrings that were
    simple and for others that were more complex. I also tested 
    that it worked for words such as "print". This failed at first
    and I realized it was becasue I was reading in the input as 
    chars instead of strings. This test helped me catch that error. 
    Additionaly, I tested using an extra whitespace and without
    the space in the beginning to make sure it produced the same
    result. 

    week 2 testing 
    My week 2 testing strategy was using diff and the referance
    file. I would write a small implementation like "print"
    then I would diff test to make sure it worked and had the 
    same output as the ref. I also used redirecting in bash 
    so that my std::cerr outputs can be separate from my cout 
    outputs. This was useful for debugging and was generally 
    cleaner to find my mistakes as well. 

    I will now walk you through my testing files and how I 
    implemented them, the test cases they check for, and my 
    overall strategy as well. 

    I started with the general_cmds.cyl file. I had not 
    added any operation functions like + -, 
    so this was just to test that things were being added 
    properly and the approopiate functions were being called. 
    The edge case is that this file doesnn't have a quit 
    command. This should end by EOF when piped into the program. 
    I then built some operations like + - and tested with the 
    test_operations.cyl. Some edge cases I tested were mod
    and divide by 0. I also tested operations on the empty 
    stack and of datums of the wrong type. I then worked on my
    comparison functions like < >. I tested with test_compare.cyl 
    which tested for edge casees such as using == on non-ints
    or using >= on non ints. When these all worked, I moved onto 
    exec. I tested using my exec_test.cyl file which had 
    nested RStrings, simple RStrings, callling of exec on the 
    wrong types and calling exec on an empty stack. When these
    edge and regular cases passed my diff, I moved onto if. 
    In if, I noticed that there were many test cases for bad
    inputs with the boolean being priorty. I therefore, 
    dedicated a good amuont of that file to testing 
    the different combinations of wrong data types on if to make
    sure the correct error message was displayed. I also tested
    if with less than 3 elems in the stack. I then built
    my file commands and wanted to really stress test my program. 
    I created a file that called all my previous files. I did 
    this to make sure nothing would crash for some reason that
    I wasn't catching. It took longer to run, but it passed. 
    Finally, I tested using the fib and factorial files provided
    by mark sheldon and the add file provided by Pippa. 
    When these all passed diff, I felt ~happy~. 