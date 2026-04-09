#include "a5.h"
#include <random>
#include <algorithm>

vector<vector<Cell>> computer_move(vector<vector<Cell>> board) 
{
    const vector<vector<Cell>> original = board;
    
    for (int col = 0; col < 7; col++) // Attempt to win w/o anvil
    {
        int row =drop_piece(board, col, Cell::Player2, false);

        if (row != -1) {
            //convert board vector to int vector (sadge, function miscommunication problem)
            vector<vector<int>> int_board = convert_to_int_board(board);

            coords move;
            move.col = col - 1;
            move.row = 5 - row;
            move.player = 2;
            if (win_con(int_board, move)) return board; // winning board is found, return the winning board

            board= original; // revert the simulation/test
        }
    }


    for (int col = 0; col < 7; col++) // Attempt to win with anvil
    {
        int row =drop_piece(board, col, Cell::Anvil2, true);
    
        if (row != -1) {
            //convert board vector to int vector (sadge, function miscommunication problem)
            vector<vector<int>> int_board = convert_to_int_board(board);

            coords move;
            move.col = col - 1;
            move.row = 5 - row;
            move.player = 2;
            if (win_con(int_board, move)) return board; // winning board is found, return the winning board

            board= original; // revert the simulation/test
        }
    }


    for (int col = 0; col < 7; col++) // Attempt to block player1's win w/o anvil
    {
        int row =drop_piece(board, col, Cell::Player1, false);
        if (row != -1) {

            vector<vector<int>> int_board = convert_to_int_board(board);

            coords move;
            move.col = col - 1;
            move.row = 5 - row;
            move.player = 1;

            if (win_con(int_board, move)) {
                board = original;
                drop_piece(board, col, Cell::Player2, false);
                return board; // return the board with blocking the player1 win move
            }
            board= original; // revert the simulation/test
        }
    }

    for (int col = 0; col < 7; col++) // Attempt to block player1's win WITH anvil
    {
        int row =drop_piece(board, col, Cell::Anvil1, true);
        if (row != -1) {

            vector<vector<int>> int_board = convert_to_int_board(board);

            coords move;
            move.col = col - 1;
            move.row = 5 - row;
            move.player = 1;

            if (win_con(int_board, move)) {
                board = original;
                drop_piece(board, col, Cell::Anvil2, true);
                return board; // return the board with blocking the player1 win move
            }
            board = original; // revert the simulation/test
        }
    }


    vector<int> columns = {0, 1, 2, 3, 4, 5, 6}; // if there is no immediate win, the computer picks a random column to place the chip.
    random_device rd;
    mt19937 g(rd());
    shuffle(columns.begin(), columns.end(), g);

    for (int col : columns) {
        int row = drop_piece(board, col, Cell::Player2, false);
        
        if (row != -1) {
            return board;
        }
        board = original;
    }


    return board; // in case of a tie or the board is full (I don't think this'll happen, but just in case)
}