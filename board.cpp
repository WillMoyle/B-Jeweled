// B-Jeweled Board Generator - BOARD CLASS FUNCTION DEFINITIONS

// Author: Will Moyle
// Date Modified: 29 Jan 2016

// C++ command line program to generate and print out an mxn board with randomly
// generated characters (from a choice of c) satisfying the following two
// conditions:
//     - There are no rows of 3 or more of the same character
//     - It is possible to swap two adjacent characters to make a row of 3

#include "board.h"


////////////////////////////////////////////////////////////////////////////////
// MAIN RUNNING LOOP
////////////////////////////////////////////////////////////////////////////////


// CONSTRUCTOR
// Performs the main running of the generator
Board::Board(std::ostream& out, std::istream& in) {
    
    // print welcome message
    welcomeMessage(out);
    
    // Loop to allow for multiple board generations
    bool loop = true;
    while (loop) {
        // receive input from user
        receiveParameters(out, in);
        
        // generate valid board
        generateBoard();
        
        // print board
        printBoard(out);
        
        // check if user wants to repeat
        loop = repeat(out, in);
    }
    
    // print goodbye message
    finalMessage(out);
}
// END OF CONSTRUCTOR


////////////////////////////////////////////////////////////////////////////////
// BOARD GENERATION
////////////////////////////////////////////////////////////////////////////////


// FUNCTION: generateBoard
// Files vector attribute with valid board satisfying game rules
void Board::generateBoard() {
    board = std::vector<std::vector<int> >(rows,std::vector<int>(columns,0));
    srand (time(NULL));
    bool possibleMove = false;
    
    // Fill row 1 and row 2
    for (int i = 0; i < 2; i++) {
        // Fill column 1 and 2
        for (int j = 0; j < 2; j++)
            board[i][j] = rand() % pieces + 1;
        // Fill remaining columns
        for (int j = 2; j < columns; j++) {
            board[i][j] = rand() % pieces + 1;
            // Check for 3 in a row to the left
            while (board[i][j] == board[i][j-1]
                   && board[i][j] == board[i][j-2])
                board[i][j] = rand() % pieces + 1;
            
            // Check if move has been created to the left
            if (!possibleMove && j >= 3) {
                if (board[i][j] != board[i][j-1]
                    && board[i][j] == board[i][j-2]
                    && board[i][j] == board[i][j-3])
                    possibleMove =true;
            }
            
            // Check if move has been created diagonally up
            if (!possibleMove && i == 2) {
                if (board[i][j] != board[i-1][j]
                    && board[i][j] == board[i-1][j-1]
                    && board[i][j] == board[i-1][j-2])
                    possibleMove =true;
            }
        }
        
    }
    
    // Fill remaining rows
    for (int i = 2; i < rows; i++) {
        // Column 1 and 2
        for (int j = 0; j < 2; j++) {
            board[i][j] = rand() % pieces + 1;
            while (board[i][j] == board[i-1][j]
                   && board[i][j] == board[i-2][j])
                board[i][j] = rand() % pieces + 1;
        }
        // Remaining columns
        for (int j = 2; j < columns; j++) {
            board[i][j] = rand() % pieces + 1;
            
            // Check for 3 in a row above or to the left
            while ((board[i][j] == board[i][j-1]
                    && board[i][j] == board[i][j-2])
                   || (board[i][j] == board[i-1][j]
                       && board[i][j] == board[i-2][j]))
                board[i][j] = rand() % pieces + 1;
            
            // Check if a move is generated to the left
            if (!possibleMove && j >= 3) {
                if (board[i][j] != board[i][j-1]
                    && board[i][j] == board[i][j-2]
                    && board[i][j] == board[i][j-3])
                    possibleMove =true;
            }
            
            // Check if a move is generated above
            if (!possibleMove && i >= 3) {
                if (board[i][j] != board[i-1][j]
                    && board[i][j] == board[i-2][j]
                    && board[i][j] == board[i-3][j])
                    possibleMove =true;
            }
            
            // Check if move is generated diagonally up
            if (!possibleMove) {
                if (board[i][j] != board[i-1][j]
                    && board[i][j] == board[i-1][j-1]
                    && board[i][j] == board[i-1][j-2])
                    possibleMove =true;
            }
            
            // Check if move is generated diagonally to the left
            if (!possibleMove) {
                if (board[i][j] != board[i][j-1]
                    && board[i][j] == board[i-1][j-1]
                    && board[i][j] == board[i-2][j-1])
                    possibleMove =true;
            }
            
        }
        
    }
    
    // if no move has been generated, create move in top left corner
    while (!possibleMove) {
        int p = rand() % pieces +1;
        if (board[0][2] != p
            && !(board[1][0] == p && board[2][0] == p)
            && !(board[1][1] == p && board[2][1] == p)
            && !(board[1][3] == p && board[2][3] == p)
            && !(columns >= 6 && board[0][4] == p && board[0][5] == p)) {
            board[0][0] = p;
            board[0][1] = p;
            board[0][3] = p;
            possibleMove = true;
        }
    }
}
// END OF FUNCTION


////////////////////////////////////////////////////////////////////////////////
// AUXILLIARY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////



// FUNCTION: welcomeMessage
// Prints a welcome message to the console
void Board::welcomeMessage(std::ostream& out) {
    out << "\nWelcome to the B-Jeweled Board Generator";
    out << "\nAuthor: Will Moyle\nLast modified: 29 January 2016\n\n";
}
// END OF FUNCTION



// FUNCTION: receiveParameters
// Receives input to set m, n and c parameters and checks validity
void Board::receiveParameters(std::ostream& out, std::istream& in) {
    
    // Receive input for row parameter
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
    rows = inputValue;
    
    // Receive input for column parameter
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
    columns = inputValue;
    
    // Receive input for number of pieces
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
    pieces = inputValue;
}
// END OF FUNCTION



// FUNCTION: printBoard
// Prints the board to the given ostream
void Board::printBoard(std::ostream& out) {
    out << "\nPRINTING BOARD:\n";
    for (int i = 0; i < rows; i++) {
        out << "\t";
        for (int j = 0; j < columns; j++)
            out << board[i][j] << " ";
        out << "\n";
    }
    out << "\n";
}
// END OF FUNCTION



// FUNCTION: stringIsInt
// Returns true if the given string represents a valid positive integer
bool Board::stringIsInt(std::string word) {
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
bool Board::repeat(std::ostream& out, std::istream& in) {
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



// FUNCTION: finalMessage
// Prints a goodbye message to the given ostream
void Board::finalMessage(std::ostream& out) {
    out << "\nGoodbye\n";
}
// END OF FUNCTION
