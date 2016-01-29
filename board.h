// B-Jeweled Board Generator - BOARD CLASS HEADER

// Author: Will Moyle
// Date Modified: 29 Jan 2016

// C++ command line program to generate and print out an mxn board with randomly
// generated characters (from a choice of c) satisfying the following two
// conditions:
//     - There are no rows of 3 or more of the same character
//     - It is possible to swap two adjacent characters to make a row of 3


#ifndef board_h
#define board_h

#include <ostream>
#include <istream>
#include <vector>
#include <string>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Board {
    // ATTRIBUTES
    int rows, columns, pieces;
    std::vector<std::vector<int> > board;
    
    // Prints a welcome message to the console
    void welcomeMessage(std::ostream& out);
    
    // Receives input to set m, n and c parameters and checks validity
    void receiveParameters(std::ostream& out, std::istream& in);
    
    // Files vector attribute with valid board satisfying game rules
    void generateBoard();
    
    // Prints the board to the given ostream
    void printBoard(std::ostream& out);
    
    // Returns true if the given string represents a valid positive integer
    bool stringIsInt(std::string word);
    
    // Returns true if user wishes to generate another board
    bool repeat(std::ostream& out, std::istream& in);
    
    // Prints goodbye message to given ostream
    void finalMessage(std::ostream& out);
    
    
public:
    
    // Constructor performs the main running of the generator
    Board(std::ostream& out, std::istream& in);
    
};











#endif