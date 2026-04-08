#ifndef A5_H
#define A5_H

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Contains structs, classes and delcarstions for the functions used in our game 

// Structs and Classes:

    // Using these to track grid and player (Sahaj)

enum class Cell{ //defining whats inside each cell
    Player1, 
    Player2,
    Anvil1,
    Anvil2,
    Empty,
};

struct Player{
        string name;
        bool is_computer = false;
        bool anvil_used = false;
        Cell piece; 
};

    // Using this for win conditions (Mengna)

struct coords{
    int col;
    int row;
    int player; //1 or 2
    bool operator==(const coords& rhs)
    {
        return col ==rhs.col && row ==rhs.row && player == rhs.player;
    }
};

// Function Declaration for win conditions (Mengna)
//see: win-function.cpp for more info

bool win_con(const vector<vector<int>>& grid, coords move); // the main win condition function to call. 

// Function Declarations for UI (Sahaj)
// see: UI_a5.cpp for more info

void title();

void rules();

void player_setup(Player &player1, Player &player2);

bool play_again();

string get_piece_line(Cell piece, int line);

vector <vector<Cell>> create_board();

void print_board(vector<vector<Cell>> &board);

int get_human_move(Player &player, vector<vector<Cell>> &board);

bool ask_for_anvil(Player &player);

int determine_first_player(Player &player1, Player &player2);

int drop_piece(vector<vector<Cell>> &board, int col, Cell piece, bool is_anvil);

int cell_to_int(Cell piece);

#endif
