#include "a5.h"

//////////////////////////////////////////////////////////////////////////////////////////

//Win Condition Function Implementations: (Mengna)

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

bool win_con(const vector<vector<int>>& grid, coords move){ //vector grid is the current grid, coords move is the col and row ints of the last move, and the player who made the move. Remember to calculate this.
    return row_con(grid,move.row,move.player)||col_con(grid,move.col,move.player)||diagonal_con(grid,move.col,move.row,move.player);
}

////////////////////////////////////////////////////////////////////////////////////////////

//UI Function Implementations: (Sahaj)

//Converting cell to int need for the win/lose/tie logic

int cell_to_int(Cell piece){
    if (piece == Cell::Player1 || piece == Cell::Anvil1) return 1;
    if (piece == Cell::Player2 || piece == Cell::Anvil2) return 2;
    
    return 0; // If empty
}

vector<vector<int>> convert_to_int_board(const vector<vector<Cell>>& board) {
    // Making sure dimensions are correct: 7 columns, 6 rows
    vector<vector<int>> int_board(7, vector<int>(6, 0));  // [col][row]
    
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 7; c++) {
            int m_row = 5 - r;  // Flip row
            int_board[c][m_row] = cell_to_int(board[r][c]);
        }
    }
    return int_board;
}
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
        if (line == 0) return " ••• ";
        if (line == 1) return " •O• ";
        if (line == 2) return " ••• ";
    }
    else if(piece == Cell::Anvil2) {
        if (line == 0) return " ••• ";
        if (line == 1) return " •X• ";
        if (line == 2) return " ••• ";
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
    cout << "3. Random\n-->";
    getline(cin, choice);

    if (choice == "1") return 1;
    if (choice == "2") return 2;
    return (rand() %2) + 1; //Random
}

int get_human_move(Player &player, vector<vector<Cell>> &board){

    (void) player;
    (void) board;
    string column;
    cout << "Enter column (from A to G):\n-->";
    cin >> column;
    cin.ignore();

    if (column.length() == 1) {
        char letter = toupper(column[0]);
              
        if (letter >= 'A' && letter <= 'G') {
            return letter - 'A' + 1;
        } else {
        cout << "Invalid input try again. Enter A-G.\n";
        }
    } else {
        cout << "Invalid input try again. Enter A-G.\n";
    }
    return -1;
}

bool ask_for_anvil(Player &player){
    (void) player;
    string choice;
    cout << "Will you use your anvil? (y/n)\n-->";
    cin >> choice;
    cin.ignore();
    return (choice == "y" || choice == "Y");
}

int drop_piece(vector<vector<Cell>> &board, int col, Cell piece, bool is_anvil){
    (void) board;
    if(board[0][col] != Cell::Empty){
        return -1; //Column would be full
    }

    if (is_anvil){
        //It will destroy everything in that column
        for (int r = 0; r < 6; r++){
            board[r][col] = Cell::Empty;
        }

        board[5][col] = piece; // drop the piece to the bottom
        return 5;
    }
    else {
        //Regular piece logic

        for (int r = 5; r >= 0; r--){ //going down the columns
            if (board[r][col] == Cell::Empty){
                board[r][col] = piece;
                return r;
            }
        }
    }
    return -1;
}

bool check_tie(const vector<vector<Cell>> &board){
    (void) board;
    for (int c = 0; c < 7; c ++){
        if (board[0][c] == Cell::Empty){
            return false; // if theres a empty cell theres no tie yet
        }
    }
    return true;
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
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//Computer AI (Mengna)
computer_return computer_move(vector<vector<Cell>> board,bool anvil_used) 
{
    const vector<vector<Cell>> original = board;
    
    for (int col = 0; col < 7; col++) // Attempt to win w/o anvil
    {
        int row =drop_piece(board, col, Cell::Player2, false);

        if (row != -1) {
            //convert board vector to int vector (sadge, function miscommunication problem)
            vector<vector<int>> int_board = convert_to_int_board(board);

            coords move;
            move.col = col;
            move.row = 5 - row;
            move.player = 2;
            if (win_con(int_board, move)){
                computer_return computer_move;
                computer_move.board=board;
                computer_move.anvil_used=false;
                computer_move.row=row;
                computer_move.col=col;
                return computer_move;
            } // winning board is found, return the winning board

            board= original; // revert the simulation/test
        }
    }

    if (anvil_used==false){
        for (int col = 0; col < 7; col++) // Attempt to win with anvil
        {
            int row =drop_piece(board, col, Cell::Anvil2, true);
        
            if (row != -1) {
                //convert board vector to int vector (sadge, function miscommunication problem)
                vector<vector<int>> int_board = convert_to_int_board(board);

                coords move;
                move.col = col;
                move.row = 5 - row;
                move.player = 2;
                if (win_con(int_board, move)){
                    computer_return computer_move;
                    computer_move.board=board;
                    computer_move.anvil_used=true;
                    computer_move.row=row;
                    computer_move.col=col;
                    return computer_move;
                }; // winning board is found, return the winning board

                board= original; // revert the simulation/test
            }
        }

        for (int col = 0; col < 7; col++) // Attempt to block player1's win WITH anvil
        {
            int row =drop_piece(board, col, Cell::Anvil1, true);
            if (row != -1) {

                vector<vector<int>> int_board = convert_to_int_board(board);

                coords move;
                move.col = col;
                move.row = 5 - row;
                move.player = 1;

                if (win_con(int_board, move)) {
                    board = original;
                    drop_piece(board, col, Cell::Anvil2, true);
                    computer_return computer_move;
                    computer_move.board=board;
                    computer_move.anvil_used=true;
                    computer_move.row=row;
                    computer_move.col=col;
                    return computer_move; // return the board with blocking the player1 win move
                }
                board = original; // revert the simulation/test
            }
        }
    }

    for (int col = 0; col < 7; col++) // Attempt to block player1's win w/o anvil
    {
        int row =drop_piece(board, col, Cell::Player1, false);
        if (row != -1) {

            vector<vector<int>> int_board = convert_to_int_board(board);

            coords move;
            move.col = col;
            move.row = 5 - row;
            move.player = 1;

            if (win_con(int_board, move)) {
                board = original;
                drop_piece(board, col, Cell::Player2, false);
                computer_return computer_move;
                computer_move.board=board;
                computer_move.anvil_used=false;
                computer_move.row=row;
                computer_move.col=col;
                return computer_move; // return the board with blocking the player1 win move
            }
            board= original; // revert the simulation/test
        }
    }


    vector<int> columns = {0, 1, 2, 3, 4, 5, 6}; // if there is no immediate win, the computer picks a random column to place the chip.
    random_device rd;
    mt19937 g(rd());
    shuffle(columns.begin(), columns.end(), g);

    for (int col : columns) {
        int row = drop_piece(board, col, Cell::Player2, false);
        
        if (row != -1) {
            computer_return computer_move;
            computer_move.board=board;
            computer_move.anvil_used=false;
            computer_move.row=row;
            computer_move.col=col;
            return computer_move;
        }
        board = original;
    }

    // in case of a tie or the board is full (I don't think this'll happen, but just in case)
    computer_return computer_move;
    computer_move.board=board;
    computer_move.anvil_used=false;
    return computer_move; 
}


/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//Main Game Loop (Sahaj)
void game_loop(){
    //===SETUP===

    Player player1, player2;
    player_setup(player1, player2);

    //Initializing players' status

    player1.anvil_used = false;
    player2.anvil_used = false;

    player1.piece = Cell::Player1;
    player2.piece = Cell::Player2;

    //create empty board
    vector<vector<Cell>> board = create_board();

    //determine who goes first
    int current_player = determine_first_player(player1, player2);

    bool game_over = false;

    //===MAIN GAME LOOP===
    while (!game_over)
    {
        //print the board
        print_board(board);

        //get current player
        Player &current = (current_player == 1) ? player1 : player2;

        //Turn info
        cout << "\n================================\n";
        cout << current.name << "'s turn!\n";
        if(!current.anvil_used){
            cout << "ANVIL still availible!\n";
        }
        cout << "\n================================\n";

        //Getting the move for each players turn
        int col = 0;
        bool use_anvil = false;

        if (current.is_computer){
            computer_return computer=computer_move(board,player2.anvil_used);
            board=computer.board;
            use_anvil = computer.anvil_used;

            vector<vector<int>> int_board = convert_to_int_board(board);

            coords move;
            move.col = computer.col;
            move.row = 5 - computer.row;
            move.player = 2;

            if (win_con(int_board, move)){
                print_board(board);
                cout << "\n HOORAY! THE COMPUTER WINS!!!\n";
                game_over = true;
            }

            //Checking for tie

            else if (check_tie(board)){
                print_board(board);
                cout << "\n IT'S A TIE!\n";
                cout << "NO more space on the board so no one wins ...\n";
                game_over = true;
            }
            if (use_anvil){
            current.anvil_used = true;
            cout << "Anvil has been used! The computer can't use it anymore this round.\n";
            }
        } 
        else { // the human player move
            col = get_human_move(current, board);

            if (col == -1){
                continue; // ask again for move because of error
            }

            if(!current.anvil_used){
                use_anvil = ask_for_anvil(current);
            }
            //dropping the piece
            int row = drop_piece(board, col-1, current.piece, use_anvil);

            if (row == -1){
                cout << "This column is full! Try another.\n";
                continue;
            }

            //Mark if anvil is used
            if (use_anvil){
                current.anvil_used = true;
                cout << "Anvil has been used! Can't use it anymore this round.\n";
            }

            //Checking for win:
            vector<vector<int>> int_board = convert_to_int_board(board);

            coords move;
            move.col = col - 1;
            move.row = 5 - row;
            move.player = cell_to_int(current.piece);

            if (win_con(int_board, move)){
                print_board(board);
                cout << "\n HOORAY! " << current.name << " WINS!!!\n";
                game_over = true;
            }

            //Checking for tie

            else if (check_tie(board)){
                print_board(board);
                cout << "\n IT'S A TIE!\n";
                cout << "NO more space on the board so no one wins ...\n";
                game_over = true;
            }
        }
    
        //Switch players turns:
        if (!game_over) {
            current_player = (current_player == 1) ? 2 : 1;
        }
    }
    
}

int main(){
    //==TITLE + RULES==
    title();
    rules();

    bool playing = true;
    while (playing){
        game_loop();
        playing = play_again();
    }
}