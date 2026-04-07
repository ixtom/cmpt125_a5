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
    bool operator==(const coords& rhs)
    {
        return col ==rhs.col && row ==rhs.row && player == rhs.player;
    }
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

bool red_test(const vector<vector<int>>& grid,coords red_coords,int player){
        while (!(red_coords.row == 5||red_coords.col==0)){
        red_coords.row ++;
        red_coords.col --;
    }
        if (red_coords==coords{0,5,player}||red_coords==coords{1,5,player}){ //checks 3 based on the diagonal line created with 05,15 as first coords
        // should return true if test passes
        for (int i=0;i<4;i++){ //checks 3 times
        if (grid[red_coords.col+i][red_coords.row-i]==player){
            int count=0;
            for (int r=i+1;r<i+4;r++){//might be a problem (r<i+4)
                if (grid[red_coords.col+r][red_coords.row-r]!=player){
                    break;
                }
                count++;
            }
            if (count == 3) return true;
            }
        }
        return false;
    }
    else if (red_coords==coords{0,4,player}||red_coords==coords{2,5,player}) //checks 2 based on 04,25
    {
        for (int i=0;i<3;i++){ //checks 2 times
        if (grid[red_coords.col+i][red_coords.row-i]==player){
            int count=0;
            for (int r=i+1;r<i+4;r++){//might be a problem (r<i+4)
                if (grid[red_coords.col+r][red_coords.row-r]!=player){
                    break;
                }
                count++;
            }
            if (count == 3) return true;
            }
        }
        return false;
    }
    else if (red_coords==coords{0,3,player}||red_coords==coords{3,5,player}) //checks 1 based on 03,35
    {
        for (int i=0;i<2;i++){ //checks 1 time
        if (grid[red_coords.col+i][red_coords.row-i]==player){
            int count=0;
            for (int r=i+1;r<i+4;r++){//might be a problem (r<i+4)
                if (grid[red_coords.col+r][red_coords.row-r]!=player){
                    break;
                }
                count++;
            }
            if (count == 3) return true;
            }
        }
        return false;
    }
    else{
        return false;
    }
}


bool diagonal_con(const vector<vector<int>>& grid, int col, int row, int player){
    //black diagonal test
    //diagonal algorithm is a bit hard to explain, it uses the same method as the rows, but based on the first coordinate in the diagonal line, it does a certain number of checks due to diagonal capacity on the board
    //see this image: (my drawing of my algorithm)
    coords red_coords ={col,row,player};
    coords black_coords ={col,row,player};
    while (!(black_coords.row == 0||black_coords.col==0)){ //first, doing the black line test
        black_coords.row --;
        black_coords.col --;
    }
    if (black_coords==coords{0,0,player}||black_coords==coords{1,0,player}){ //checks 3 based on the diagonal line created with 00,10 as first coords
        // should return true if test passes
        for (int i=0;i<4;i++){ //checks 3 times
        if (grid[black_coords.col+i][black_coords.row+i]==player){
            int count=0;
            for (int r=i+1;r<i+4;r++){//might be a problem (r<i+4)
                if (grid[black_coords.col+r][black_coords.row+r]!=player){
                    break;
                }
                count++;
            }
            if (count == 3) return true;
            }
        }
        return red_test(grid,red_coords,player);
    }
    else if (black_coords==coords{0,1,player}||black_coords==coords{2,0,player}) //checks 2 based on 01,20
    {
        for (int i=0;i<3;i++){ //checks 2 times
        if (grid[black_coords.col+i][black_coords.row+i]==player){
            int count=0;
            for (int r=i+1;r<i+4;r++){//might be a problem (r<i+4)
                if (grid[black_coords.col+r][black_coords.row+r]!=player){
                    break;
                }
                count++;
            }
            if (count == 3) return true;
            }
        }
        return red_test(grid,red_coords,player);
    }
    else if (black_coords==coords{0,2,player}||black_coords==coords{3,0,player}) //checks 1 based on 02,30
    {
        for (int i=0;i<2;i++){ //checks 1 time
        if (grid[black_coords.col+i][black_coords.row+i]==player){
            int count=0;
            for (int r=i+1;r<i+4;r++){//might be a problem (r<i+4)
                if (grid[black_coords.col+r][black_coords.row+r]!=player){
                    break;
                }
                count++;
            }
            if (count == 3) return true;
            }
        }
        return red_test(grid,red_coords,player);
    }
    else{
        // return test red lines. if else is reached again on red lines, return false
        return red_test(grid,red_coords,player);

    }
}

bool win_con(const vector<vector<int>>& grid, coords move){ //vector grid is the current grid, coords move is the col and row ints of the last move. Remember to calculate this.
    return row_con(grid,move.row,move.player)||col_con(grid,move.col,move.player)||diagonal_con(grid,move.col,move.row,move.player);
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