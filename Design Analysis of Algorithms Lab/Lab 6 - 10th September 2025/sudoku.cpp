#include <bits/stdc++.h>
using namespace std;

#define N 9

bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number is not in the current row
    for(int x = 0; x < N; x++) 
        if(grid[row][x] == num) return false;

    // Check if the number is not in the current column
    for(int x = 0; x < N; x++) 
        if(grid[x][col] == num) return false;

    // Check if the number is not in the current 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for(int i = 0; i < 3; i++) 
        for(int j = 0; j < 3; j++) 
            if(grid[i + startRow][j + startCol] == num) return false;

    return true;
}

bool solveSudoku(int grid[N][N]) {
    // Try to fill an empty cell
    for(int row = 0; row < N; row++) {
        for(int col = 0; col < N; col++) {
            // If the cell is empty (contains 0)
            if(grid[row][col] == 0) {
                // Try all numbers from 1 to 9
                for(int num = 1; num <= 9; num++) {
                    // If the number is safe to place
                    if(isSafe(grid, row, col, num)) {
                        grid[row][col] = num;  // Place the number
                        // Recurse to solve the next part of the puzzle
                        if(solveSudoku(grid)) return true;
                        grid[row][col] = 0;  // Backtrack if no solution found
                    }
                }
                return false;  // No valid number can be placed in this cell
            }
        }
    }
    return true;  // Puzzle solved
}

void printGrid(int grid[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) 
            cout << grid[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    // Modified Sudoku puzzle with a valid solution
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if(solveSudoku(grid)) 
        printGrid(grid);  // Print the solved grid
    else 
        cout << "No solution exists";  // In case no solution is found
}