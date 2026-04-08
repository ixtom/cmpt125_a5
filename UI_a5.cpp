#include "cmpt_error.h"
#include <string>
#include <iostream>

using namespace std;

// Struct and class: 

struct Player{
        string name;
        bool is_computer = false;
        bool anvil_used = false;
        Cell piece; 
};

enum class Cell{ //defining whats inside each cell
    Player1, 
    Player2,
    Anvil1,
    Anvil2,
    Empty,
};


// Function Declarations:
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
bool is_column_full(vector<vector<Cell>> &board, int col);

//Converting cell to int 

// Making the Anvils:
// Doing it line by line


string get_piece_line(Cell piece, int line){
    // line = 0 (top) line = 1 (middle) line = 2 (bottom)

    if (piece == Cell::Empty){
        return "     ";
    }

    //Player tokens
    else if(piece == Cell::Player1) {
        if (line == 0) return " ––– ";
        if (line == 1) return " |O| ";
        if (line == 2) return " ––– ";
    }
    else if(piece == Cell::Player2) {
        if (line == 0) return " ––– ";
        if (line == 1) return " |X| ";
        if (line == 2) return " ––– ";
    }

    // Anvils
    else if(piece == Cell::Anvil1) {
        if (line == 0) return " ### ";
        if (line == 1) return " #O# ";
        if (line == 2) return " ### ";
    }
    else if(piece == Cell::Anvil2) {
        if (line == 0) return " ### ";
        if (line == 1) return " #X# ";
        if (line == 2) return " ### ";
    }
    return "     ";
}

// Making and printing the Board:

vector <vector<Cell>> create_board(){
    return vector<vector<Cell>>(6, vector<Cell>(7, Cell::Empty)); 
}

void print_board(vector<vector<Cell>> &board){
    cout << "     A     B     C     D     E     F     G\n";

    cout << "  +-----+-----+-----+-----+-----+-----+-----+\n";

    for (int r = 0; r < 6; r++){
        for (int line = 0; line < 3; line++){
                cout << "  ";
                for (int c = 0; c < 7; c++){
                cout << "|" << get_piece_line(board[r][c], line);
                }
            cout << "|\n";
        }

        if (r < 5){
            cout << "  +-----+-----+-----+-----+-----+-----+-----+\n";
        }
    }

    cout << "  +-----+-----+-----+-----+-----+-----+-----+\n";
} 
// Function Definitions (UI Related):

void title(){
    cout <<"░█████╗░░█████╗░███╗░░██╗███╗░░██╗███████╗░█████╗░████████╗\n";
    cout <<"██╔══██╗██╔══██╗████╗░██║████╗░██║██╔════╝██╔══██╗╚══██╔══╝\n";
    cout <<"██║░░╚═╝██║░░██║██╔██╗██║██╔██╗██║█████╗░░██║░░╚═╝░░░██║░░░\n";
    cout <<"██║░░██╗██║░░██║██║╚████║██║╚████║██╔══╝░░██║░░██╗░░░██║░░░\n";
    cout <<"╚█████╔╝╚█████╔╝██║░╚███║██║░╚███║███████╗╚█████╔╝░░░██║░░░\n";
    cout <<"░╚════╝░░╚════╝░╚═╝░░╚══╝╚═╝░░╚══╝╚══════╝░╚════╝░░░░╚═╝░░░\n";
                                                              

    cout <<"███████╗░█████╗░██╗░░░██╗██████╗░\n";
    cout <<"██╔════╝██╔══██╗██║░░░██║██╔══██╗\n";
    cout <<"█████╗░░██║░░██║██║░░░██║██████╔╝\n";
    cout <<"██╔══╝░░██║░░██║██║░░░██║██╔══██╗\n";
    cout <<"██║░░░░░╚█████╔╝╚██████╔╝██║░░██║\n";
    cout <<"╚═╝░░░░░░╚════╝░░╚═════╝░╚═╝░░╚═╝\n\n";    

    cout <<"█▀█ █▀▀ ▄▀█ █▀▄ █▄█   ▀█▀ █▀█   █░█░█ █ █▄░█   █▀▀ █▀█ █░█ █▀█   █ █▄░█   ▄▀█   █▀█ █▀█ █░█░█ ▀█\n";
    cout <<"█▀▄ ██▄ █▀█ █▄▀ ░█░   ░█░ █▄█   ▀▄▀▄▀ █ █░▀█   █▀░ █▄█ █▄█ █▀▄   █ █░▀█   █▀█   █▀▄ █▄█ ▀▄▀▄▀ ░▄\n\n\n";
}
void rules(){ 
    cout << "==================================================================\n";                                           
    cout << "𝗙𝗶𝗿𝘀𝘁 𝘆𝗼𝘂 𝗺𝘂𝘀𝘁 𝗺𝗮𝘀𝘁𝗲𝗿 𝘁𝗵𝗲 𝗿𝘂𝗹𝗲𝘀:\n\n";
    cout << "• Choose whether to play against a friend or a computer.\n\n";
    cout << "• Each player will have their unique anvil piece\n\n";
    //print anvil pieces as examples
    cout << "• Players will take turns dropping their anvil pieces into the columns of the grid.\n\n";
    cout << "• The first player to connect four of their pieces in a row is the winner!\n";
    cout << " - The four pieces can be connected horizontally, vertically, or diagonally.\n\n";
    cout << "Can you become the ultimate Connect Four champion? Let's find out!\n";
    cout << "==================================================================\n\n";
}

void player_setup(Player &player1, Player &player2){

    cout <<"█▀█ █░░ ▄▀█ █▄█ █▀▀ █▀█   █▀ █▀▀ ▀█▀   █░█ █▀█ ▀\n";
    cout <<"█▀▀ █▄▄ █▀█ ░█░ ██▄ █▀▄   ▄█ ██▄ ░█░   █▄█ █▀▀ ▄\n\n";

    cout << "Enter name for Player 1: \n--> ";
    string line;
    getline(cin, line);
    player1.name = line;

    while (true) {
        cout << "Who will you play with?\n";
        cout << "A friend (1 or f) or a Computer (2 or c)\n--> ";
        getline(cin, line);
        cout << "\n";
        if (line == "1" || line == "f"){
            cout << "𝗠𝗢𝗗𝗘: 𝗣𝗹𝗮𝘆𝗶𝗻𝗴 𝗮𝗴𝗮𝗶𝗻𝘀𝘁 𝗮 𝗙𝗿𝗶𝗲𝗻𝗱\n\n";
            cout << "Enter name for Player 2:\n--> ";
            getline(cin, line);
            player2.name = line;
            player2.is_computer = false;
            break;
        }
        else if (line == "2" || line == "c"){
            cout << "𝗠𝗢𝗗𝗘: 𝗣𝗹𝗮𝘆𝗶𝗻𝗴 𝗮𝗴𝗮𝗶𝗻𝘀𝘁 𝘁𝗵𝗲 𝗖𝗼𝗺𝗽𝘂𝘁𝗲𝗿";
            player2.name = "Computer";
            player2.is_computer = true;

            break;
        } else {
            cout << "Error: invalid input, try again.\n--> ";
        }
    }
            
    cout << "\n\n" << "█▀▀ ▄▀█ █▀▄▀█ █▀▀   █▀▄▀█ █▀█ █▀▄ █▀▀ ▀   █▀█ █▄░█\n";
    cout <<"█▄█ █▀█ █░▀░█ ██▄   █░▀░█ █▄█ █▄▀ ██▄ ▄   █▄█ █░▀█\n\n";

    cout << "===================================================================\n";
    cout << player1.name << " VS " << player2.name << "\n";
    cout << "===================================================================\n";
}

int determine_first_player(Player &player1, Player &player2){
    string choice;
    cout << "Who goes first?\n";
    cout << "1. " << player1.name << "\n";
    cout << "2. " << player2.name << "\n";
    cout << "1. Random\n-->";
    getline(cin, choice);

    if (choice == "1") return 1;
    if (choice == "2") return 2;
    return (rand() %2) + 1; //Random
}

int get_human_move(Player &player, vector<vector<Cell>> &board){
    int column;
    cout << "Enter column (from A to G):\n-->";
    cin >> column;
    cin.ignore();

    return column;
}

int ask_for_anvil(){
    
}
bool play_again(){
    while (true){
        cout << "Play again?\n";
        cout << "Yes (1 or y) or No (2 or n)?\n--> ";
        string line;
        getline(cin, line);

        if (line == "1" || line == "y"){
            return true;
        }
        else if(line == "2" || line == "n"){
            cout << "Thanks for playing!\n";
            return false;
        } else {
            cout << "Error: invalid input, try again.\n--> ";
        }
    }
}


// The Computer Strategy:



// Main Function:

int main(){
    title();
    rules ();

    return 0;
}
