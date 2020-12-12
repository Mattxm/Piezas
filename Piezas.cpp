#include "Piezas.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/


Piezas::Piezas()
{
    reset();
}

/* Added local function for more reusability */
void SwitchTurn(Piece &turn){
    if (turn == X)
        turn = O;
    else
        turn = X;
}


/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    board.clear();
    turn = X;
    for(int i= 0; i < BOARD_ROWS; i++){
        std::vector<Piece> temp; 
        for(int j = 0; j < BOARD_COLS; j++){
            temp.push_back(Blank);
        }
        board.push_back(temp);   
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    if ((column <= 3) && (column >= 0)){
        for(int i=BOARD_ROWS; i -- > 0;){
            if (board[i][column] == Blank){
                board[i][column] = turn;
                SwitchTurn(turn);
                return board[i][column];
                }
        }
        SwitchTurn(turn);
        return Blank;
    }
    else{
        SwitchTurn(turn);
        return Invalid;
    }
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    try{
        cout << board[BOARD_ROWS-1 - row][column];
        return board[BOARD_ROWS-1 - row][column];
    }
    catch (const std::out_of_range& oor){
        return Invalid;
    }
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{ 
    if (count(board[0].begin(), board[0].end(), Blank) == 0){
        int lx = 0;
        int lo = 0;
        int cx = 0;
        int co = 0;
        Piece last = Blank;
        Piece cur = Blank;
        for (auto x : board){
            for (auto y : x){
                cur = y;
                if (cur != last){
                    if (cur == X)
                        cx = 1;
                    if (cur == O)
                        co = 1;
                }
                else{
                    if (cur == X)
                        cx++;
                    if (cur == O)
                        co++;
                }
                last = cur;
                if (cx > lx)
                    lx = cx;
                if (co > lo)
                    lo = co;
            }
            cx = 0;
            co = 0;
        }

        last = Blank;
        for (int i = 0; i < BOARD_COLS; i++)
        {
            for (int j = 0; j < BOARD_ROWS; j++)
            {
                cur = board[j][i];
                if (cur != last){
                    if (cur == X)
                        cx = 1;
                    if (cur == O)
                        co = 1;
                }
                else{
                    if (cur == X)
                        cx++;
                    if (cur == O)
                        co++;
                }
                last = cur;
                if (cx > lx)
                    lx = cx;
                if (co > lo)
                    lo = co;

            }
            cx = 0;
            co = 0;
        }
        
        if (lx > lo)
            return X;
        else if (lo > lx)
            return O;
        else return Blank;
    }
    return Invalid;
}