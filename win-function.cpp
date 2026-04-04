#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// win functions to call to check for win conditions
// - Mengna
struct coords{
    int col;
    int row;
    int player; //1 or 2
};

bool row_con(const vector<vector<int>>& grid, int row, int player){
    for (int i=0;i<4;i++){ //checks column 0-3 to see if they have a chip
        if (grid[i][row]==player){
            int count=0;
            for (int r=i+1;r<i+4;r++){
                if (grid[r][row]!=player){
                    break;
                }
                count++;
            }
            if (count == 3) return true;
        }
    }
    return false;
}

bool col_con(const vector<vector<int>>& grid, int col, int player){
    for (int i=0;i<3;i++){ //checks row 0-2 to see if they have a chip
        if (grid[col][i]==player){
            int count=0;
            for (int r=i+1;r<i+4;r++){
                if (grid[col][r]!=player){
                    break;
                }
                count++;
            }
            if (count == 3) return true;
        }
    }
    return false;
}

bool diagonal_con(const vector<vector<int>>& grid, int col, int row, int player){}

bool win_con(const vector<vector<int>>& grid, coords move){ //vector grid is the current grid, coords move is the col and row ints of the last move. Remember to calculate this.
    return row_con(grid,move.row,move.player)||col_con(grid,move.col,move.player||diagonal_con(grid,move.col,move.row,move.player));
}

int main(){
    vector<vector<int>> verticalWin = {
    {1, 1, 1, 1, 0, 0}, // Column 0: Four 1s stacked from bottom
    {0, 0, 0, 0, 0, 0}, // Column 1
    {0, 0, 0, 0, 0, 0}, // Column 2
    {0, 0, 0, 0, 0, 0}, // Column 3
    {0, 0, 0, 0, 0, 0}, // Column 4
    {0, 0, 0, 0, 0, 0}, // Column 5
    {0, 0, 0, 0, 0, 0}  // Column 6
};
    coords move ={0,3,1};
    if (win_con(verticalWin,move)){
        cout<<"win!";
    }
    else{
        cout<<"lose...";
    }
}