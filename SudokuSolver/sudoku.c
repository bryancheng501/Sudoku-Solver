//Sudoku Solver
//  Solves a standard 9x9 sudoku board using the backtracking algorithm
//  Created by Bryan Cheng

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



void printBoard(int board[9][9]);
bool solveBoard(int board[9][9]);
bool findEmptyPosition(int board[9][9], int *row, int *col);
bool isValid(int board[9][9], int row, int col, int num);
bool checkRow(int board[9][9], int row, int num);
bool checkCol(int board[9][9], int col, int num);
bool checkGrid(int board[9][9], int row, int col, int num);

/*
int main(){
    // 9x9 grid representing sudoku board
    //  0 represents an empty value
   

    printf("Starting board:\n");
    printBoard(board);

    if (!solveBoard(board)) printf("No Solution :(\n");
    else printBoard(board);
    
    return(0);
    
}
*/

//print out the sudoku board
void printBoard(int board[9][9]){
    printf("-----------------\n");
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j++){
            printf("%i ", board[i][j]);
        }
        printf("\n");
    }
    printf("-----------------\n");
}

//solve a sudoku board using backtracking algorithm
//  returns true with solved board if solvable
//  returns false if board is unsolvable
bool solveBoard(int board[9][9]){

    printBoard(board);

    int row, col;
    //find next empty position
    if (!findEmptyPosition(board, &row, &col)){
        return true; //board has been solved!
    }

    //try putting numbers into next empty position
    for (int i = 1; i < 10; i ++){
        //check if number is valid in next position
        if (isValid(board, row, col, i)){
            board[row][col] = i;

            //recursive call:
            //  if it returns false, backtrack
            if (solveBoard(board)) return true;

            board[row][col] = 0;
        }
    }

    return false;
}

//find next empty position in the board
//  returns false if board is complete
bool findEmptyPosition(int board[9][9], int *row, int *col){

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (board[i][j] == 0){
                *row = i; 
                *col = j;
                return true;
            }
        }
    }

    return false;
}

bool isValid(int board[9][9], int row, int col, int num){
    return  checkRow(board, row, num) && 
            checkCol(board, col, num) && 
            checkGrid(board, row, col, num);
}

//check if value matches any other values in the row
//  return true if value does not match others in same row
bool checkRow(int board[9][9], int row, int num){
    for (int i = 0; i < 9; i++){
        if (board[row][i] == num) return false;
    }
    return true;
}

//check if value matches any other value in the col
//  return true if value does not match others in same column
bool checkCol(int board[9][9], int col, int num){
    for (int i = 0; i < 9; i ++){
        if (board[i][col] == num) return false;
    }
    return true;
}

//check if value matches any other value in the grid
// return true if value does not match others in same grid
bool checkGrid(int board[9][9], int row, int col, int num){
    //compute which 'grid' we're in, from {{0,0}, {0,1}, ..., {2,2}}
    int gridRow = row / 3;
    int gridCol = col / 3;

    for (int i = 0; i < 3; i ++){
        for (int j = 0; j < 3; j ++){
            if (board[i + gridRow * 3][j + gridCol * 3] == num) return false;
        }
    }
    return true;
}