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

class Board {
    int m, n, c;
    std::vector<std::vector<int> > board;
    
    
    
    // FUNCTION: welcomeMessage
    // Prints a welcome message to the console
    void welcomeMessage(std::ostream& out) {
        out << "\nWelcome to the B-Jeweled Board Generator";
        out << "\nAuthor: Will Moyle\nLast modified: 29 January 2016";
    }
    // END OF FUNCTION
    
    
    
    void receiveParameters(std::ostream& out, std::istream& in) {
        
        std::string inputString;
        out << "\nNumber of rows (must be greater than 3): ";
        std::getline(in, inputString);
        
        bool invalidInput = true;
        int inputValue;
        
        if (stringIsInt(inputString)) {
            inputValue = std::stoi(inputString);
            if (inputValue > 3)
                invalidInput = false;
        }
        
        while (invalidInput) {
            out << "Invalid input. Please try again: ";
            std::getline(in, inputString);
            
            if (stringIsInt(inputString)) {
                inputValue = std::stoi(inputString);
                if (inputValue > 3)
                    invalidInput = false;
            }
        }
        
        m = inputValue;
        
        out << "\nNumber of columns (must be greater than 3): ";
        std::getline(in, inputString);
        
        invalidInput = true;
        
        if (stringIsInt(inputString)) {
            inputValue = std::stoi(inputString);
            if (inputValue > 3)
                invalidInput = false;
        }
        
        while (invalidInput) {
            out << "Invalid input. Please try again: ";
            std::getline(in, inputString);
            
            if (stringIsInt(inputString)) {
                inputValue = std::stoi(inputString);
                if (inputValue > 3)
                    invalidInput = false;
            }
        }
        
        n = inputValue;
        
        out << "\nNumber of pieces (must be greater than 2): ";
        std::getline(in, inputString);
        
        invalidInput = true;
        
        if (stringIsInt(inputString)) {
            inputValue = std::stoi(inputString);
            if (inputValue > 2)
                invalidInput = false;
        }
        
        while (invalidInput) {
            out << "Invalid input. Please try again: ";
            std::getline(in, inputString);
            
            if (stringIsInt(inputString)) {
                inputValue = std::stoi(inputString);
                if (inputValue > 2)
                    invalidInput = false;
            }
        }
        
        c = inputValue;
    }
    
    void generateBoard() {
        board = std::vector<std::vector<int> >(m,std::vector<int>(n,c));
    }
    
    void printBoard(std::ostream& out) {
        out << "\nPRINTING BOARD:\n";
        for (int i = 0; i < m; i++) {
            out << "\t";
            for (int j = 0; j < n; j++)
                out << board[i][j] << " ";
            out << "\n";
        }
        out << "\n";
    }
    
    // FUNCTION: stringIsInt
    // Returns true if the given string represents a valid positive integer
    bool stringIsInt(std::string word) {
        int len = word.length();
        if (len == 0)
            return false;
        int position = 0;
        while (position < len) {
            if (word[position] < '0' || word[position] > '9')
                return false;
            position++;
        }
        return true;
    }
    // END OF FUNCTION
    
    
    
    // FUNCTION: repeat
    // Returns true if user wishes to generate another board
    bool repeat(std::ostream& out, std::istream& in) {
        std::string userInput;
        out << "\nDo you wish to generate another board? (Y/N) ";
        std::getline(in, userInput);
        
        while (userInput.compare("Y") && userInput.compare("N")
               && userInput.compare("y") && userInput.compare("n")) {
            out << "\nInvalid input. Please enter 'Y' or 'N': ";
            std::getline(in, userInput);
        }
        
        if (!userInput.compare("N") || !userInput.compare("n"))
            return false;
        return true;
    }
    // END OF FUNCTION
    
    
    void finalMessage(std::ostream& out) {
        out << "\nGoodbye\n";
    }
    
    
public:
    
    Board(std::ostream& out, std::istream& in) {
        
        welcomeMessage(out);
        
        // Loop to allow for multiple conversions
        bool loop = true;
        while (loop) {
            receiveParameters(out, in);
            generateBoard();
            printBoard(out);
            
            loop = repeat(out, in);
        }
        
        finalMessage(out);
    }
    
    
    
};











#endif