###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
### Compiles all files cpp and .h files. 
### The executable made is called CalcYouLater 
### When it is run, it will use main.cpp as well 
### Author:  Nadim Barakat
### 3/4/2022
### CS 15 Proj 2

# this is needed to have make follow symlinks in dependency lists 
MAKEFLAGS += -L 



CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


# creates executable to run entire program 
CalcYouLater: main.o DatumStack.o Datum.o RPNCalc.o
	${CXX} ${LDFLAGS} -o $@ $^

# used mainly for week 1 testing 
parser.o: parser.cpp DatumStack.h Datum.h 
	$(CXX) $(CXXFLAGS) -c parser.cpp 	


main.o: main.cpp Datum.h DatumStack.h parser.o
	$(CXX) $(CXXFLAGS) -c main.cpp 


unit_test: unit_test_driver.o DatumStack.o Datum.o parser.o RPNCalc.o
	$(CXX) $(CXXFLAGS) $^

#does not delete datum.o 
clean: 
	rm main.o DatumStack.o parser.o 
##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
