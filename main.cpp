/*
File Name: ProjectFive.cpp
Purpose: Connect Four
Work with 2D arrays and classes
Alex Reynen
*/

#include <iostream>
#include <Windows.h>

using namespace std;

static const int WIDTH = 6;
static const int HEIGHT = 7;

class Board {
public:
    Board();

    void loopGame();

private:
    void hostGame();

    char board[WIDTH][HEIGHT];

    void printBoard();

    bool isMoveLegal(int col);

    void makeMove(char player);

    bool colFull(int col);

    bool isFull();

    bool hasWon(char player);

    void announceWinner(char winner);

    int times = 0;
};

int main() {
    Board game;
    game.loopGame();
}

/*
Function: loopGame
purpose: Loops the hostGame function
Input: N/A
returns: N/A
*/
void Board::loopGame() {
    char contin = 'y';

    hostGame();
    cout << "Play again? (y/n): ";
    cin >> contin;
    if (contin == 'y') {
        for (auto &i : board) {
            for (auto &j : i) {
                j = ' ';
            }
        }
        loopGame();
    }
    if (times == 0)
        system("pause");
    times--;
}

/*
Function: Board (default constructor)
Purpose: Initilizes the board with blanks
Input: N/A
Returns: N/A
*/
Board::Board() {
    for (auto &i : board) {
        for (auto &j : i) {
            j = ' ';
        }
    }
}

/*
Function: printBoard
Purpose: prints it to the console
Input: N/A
Returns: N/A
*/
void Board::printBoard() {
    cout << "\n\n";
    for (auto &i : board) {
        cout << "|";
        for (auto &j : i) {
            cout << j;
            cout << "|";
        }
        cout << endl;
    }
    cout << "_______________\n";
    cout << " 0 1 2 3 4 5 6" << endl << endl;
}

/*
Function: isMoveLegal (I split this into this and colNotFull)
Purpose: checks that the move is in the right area (0<=x<=6))
Input: col (the player's choice of where to move)
Returns: true if move is valid, false if invalid
*/
bool Board::isMoveLegal(const int col) {
    return (col <= WIDTH && col >= 0);
}

/*
Function: makeMove
Purpose: prompts the correct player to make a move and to hit the right col
Input: player (either X or O to place the thing)
Returns: N/A
*/
void Board::makeMove(char player) {
    int col;
    printBoard();
    cout << "Player ";
    cout << player;
    cout << " select a column to play in: ";
    cin >> col;

    while (!isMoveLegal(col) || colFull(col)) {
        do {
            cout << "Select a valid column: ";
            cin.clear();
            cin.ignore(100, '\n');
            cin >> col;
        } while (cin.fail());
    }

    for (int i = WIDTH; i >= 0; i--) {
        if (board[i][col] == ' ') {
            board[i][col] = player;
            break;
        }
    }
}

/*
Function: colNotFull
Purpose: checks to see if all possible moves in the col are full
Input: col (the player's choice of where to move)
Returns: true if not full, false if cant play
*/
bool Board::colFull(const int col) {
    return board[0][col] != ' ';
}

/*
Function: isFull
Purpose: checks to see if all parts of the board are full
Input: N/A
Returns: true if its full, false if not full
*/
bool Board::isFull() {
    int blankSpaces = 0;
    for (auto &i : board) {
        for (auto &j : i) {
            if (j == ' ') {
                return true;
            }
        }
    }
    return false;
}

/*
Function: hasWon
Purpose: checks to see if 4 of a kind are present
Input: player (either X or O win)
Returns: true if player has won, false if the game must go on
*/
bool Board::hasWon(char player) {
    //horizontal win condition
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT - 3; j++) {
            if (board[i][j] == player && board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] &&
                board[i][j] == board[i][j + 3])
                return true;
        }
    }

    //vertical win condition
    for (int i = 0; i < HEIGHT - 3; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == player && board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] &&
                board[i][j] == board[i + 3][j]) {
                return true;
            }
        }
    }

    //diagonal right (\) win condition
    for (int i = 0; i < HEIGHT - 3; i++) {
        for (int j = 3; j > -1; j--) {
            if (board[i][j] == player && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] &&
                board[i][j] == board[i + 3][j + 3])
                return true;
        }
    }

    //diagonal left (/) win condition
    for (int i = 0; i < HEIGHT - 3; i++) {
        for (int j = 3; j < HEIGHT; j++) {
            if (board[i][j] == player && board[i][j] == board[i + 1][j - 1] && board[i][j] == board[i + 2][j - 2] &&
                board[i][j] == board[i + 3][j - 3])
                return true;
        }
    }
    //if no conditions met, player has not won, thus false
    return false;
}

/*
Function: announceWinner
Purpose: prints the result
Input: winner (the player who won in hostGame)
Returns: N/A
*/
void Board::announceWinner(char winner) {
    printBoard();
    if (winner != 'C') {
        cout << winner;
        cout << " wins!";
    } else {
        cout << "It's a tie! No one wins.";
    }
    cout << endl;
}

/*
Function: hostGame
Purpose: plays the game, implements elements of the above functions
Input: N/A
Returns: N/A
*/
void Board::hostGame() {
    char winner;
    do {
        makeMove('X');
        if (hasWon('X')) {
            winner = 'X';
            break;
        }
        if (!isFull()) {
            winner = 'C';
            break;
        }
        makeMove('O');
        if (hasWon('O')) {
            winner = 'O';
            break;
        }
        if (!isFull()) {
            winner = 'C';
            break;
        }
    } while (true);

    announceWinner(winner);
}