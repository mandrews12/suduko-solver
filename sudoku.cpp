
#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// reads a file containing a sudoku puzzle represented as
// 9 rows, each consisting of 9 comma-separated values
Sudoku::Sudoku(const char *fname) {
    // create a file reader stream to read data from a file
    ifstream infile;

    // will store lines and numbers
    string line, number;

    // index to write value to in puzzle
    int i = 0;

    // open a stream to the given file
    infile.open(fname);

    // get a line of input from the file
    while(getline(infile, line)) {
        // store the line inside a stringstream
        stringstream parser(line);
        // use stringstream to split line along ','
        while(getline(parser, number, ',')) {
            // convert string to an integer, store it, and update iterator
            puzzle[i++] = stoi(number);
        }
    }
    // close the filestream once we are done wiht it
    infile.close();
}

// destruct Sudoku object
Sudoku::~Sudoku() {
    // since we never allocated any memory on the heap, we don't need
    // to define behavior for the deconstructor
}

// this is the funciton call which will be made by the autograder to test
// your implementation for problem 3. It takes no parameters and
// should overwrite the 0s in puzzle to so that it represents a solved puzzle
bool Sudoku::r_solve(int index, int col) {
    // checks if puzzle has been completly solved
    if ((index + 9*col)>= 81) {
        return true;
    }
    
    // makes sure index stays less than max col
    if (index == 9) {
        col += 1;
        index = 0;
    }
    // if puzzle is already filled move to next cell
    if (puzzle[index + 9*col] > 0) {
        return r_solve(index + 1, col);
    }
     
    // makes sure number is not in same row, col, and box
    for (int num = 1; num < 10; num++){
        bool good = true;
        // check if same number is already in row or column
        for (int i = 0; i < 9; i++){
            if ((puzzle[i + 9*col] == num)||(puzzle[index + 9*i] == num)){
                good = false;
            }
        }
        // check if same num is in box
        int firstI = index - index % 3;
        int firstC = col - col % 3;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (puzzle[(firstI+i)+9*(firstC+j)] == num){
                    good =  false;
                }
            }
        }
	  
        // as long as move is allowed change the cell and try next cell
        if (good){
            puzzle[index + 9*col] = num;
            if(r_solve(index+1, col)) {
                return true;
            }
        }
        // if num does not work return the cell to 0
        puzzle[index + 9*col] = 0;

    }
    return false;
}

// this function prints your puzzle in 2D format with commas
// separating your values
void Sudoku::print() {
    for(int i = 0; i < 9; i++) {
        std::cout << puzzle[i*9];
        int base = i*9;
        for(int offset = 1; offset < 9; offset++) {
            std::cout << ',' << puzzle[base + offset];
        }
        std::cout << std::endl;
    }
}

void Sudoku::solve() {
    bool found;
    found = r_solve(0,0);
}
