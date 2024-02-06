
#include "sudoku.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

Sudoku::Sudoku() {

}

Sudoku::~Sudoku() {

}

Sudoku::Sudoku(std::string f_name) {
    // Generate a board from the give file
    // create a file reader stream to read data from a file

    // create vector and string to store data from file and open file
    vector<int> my_nums;
    string line;

    ifstream infile;
   
    infile.open(f_name);

    // get data from the file and store in vector
    while(getline(infile, line)) {
        
        stringstream current(line);

        int my_int;
        while(current >> my_int){
            my_nums.push_back(my_int);
        }
    }
    
    // close the file
    infile.close();

    // convert file data to sudoku board
    int a = 0;
    for(int j = 0; j < 9; j++) {
        for(int k = 0; k < 9; k++) {
            board[j][k] = my_nums[a];
            a += 1;
        }
    }

    
}

bool Sudoku::solve(unsigned int row,unsigned int col) {
    //1) If we have filled the entire board,  return true
    if(row >= 8 && col >= 9) {
        return true;
    }
    
    // bounds checks the col int
    if(col == 9) {
        row += 1;
        col = 0;
    }
    
    // if the cell is already filled, recurse to next cell untill you find an empty cell
    if(board[row][col] > 0) {
        return solve(row,col+1);
    }
    

    //2) For each digit 1-9:
    for(int i = 1; i <=9; i++) {
	//- If this digit can be placed in this cell
        if(is_valid(row,col,i)) {
            //- Place the digit
            board[row][col] = i;
            //- Recurse to the next empty cell.
            //- If that recursive call returns true
            if(solve(row,col+1)) {
                return true;
            }
            
        }
        board[row][col] = 0;
    }
    return false;
}

// If this is an empty space & the given number does not exist in the same
// row, column, or box then it will return true.
bool Sudoku::is_valid(unsigned int row, unsigned int col, int num){
    return (this->board)[row][col] == 0 && !check_row(row, num) && !check_col(col, num)&& !check_box(row - row % 3, col - col % 3, num);
}

// checks if num is already in the row
bool Sudoku::check_row(unsigned int row, unsigned int num){
    bool found = false;
    for(int i = 0; i < 9; i++) {
        if(board[row][i] == num) {
            found = true;
        }
    }
    return found;
}

// checks if num is already in the col
bool Sudoku::check_col(unsigned int col, unsigned int num){
    bool found = false;
    for(int i = 0; i < 9; i++) {
        if(board[i][col] == num) {
            found = true;
        }
    }
    return found;
}

// checks if num is already in the 3x3 box
bool Sudoku::check_box(unsigned int boxStartRow, unsigned int boxStartCol, unsigned int num){
    bool found = false;
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(board[boxStartRow+i][boxStartCol+j] == num) {
                found = true;
            }
        }
    }
    return found;
}

void Sudoku::display_board(){
    for (unsigned int i = 0; i < this->BOARD_SIZE; i++) {
        for (unsigned int j = 0; j < this->BOARD_SIZE; j++){
            std::cout << (this->board)[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char * argv[])
{
    std::string f_name(argv[1]);

    Sudoku s(f_name);
    
    s.solve(0,0);

    s.display_board();

    return 0;
}
