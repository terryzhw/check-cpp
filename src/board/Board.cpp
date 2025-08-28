#include "Board.h"
#include "../pieces/Pawn.h"
#include "../pieces/Rook.h"
#include <iostream>

Board::Board() {
    chessboard = std::vector<std::vector<Tile>>(8, std::vector<Tile>(8));

    for (int col = 0; col < 8; col++) {
        chessboard[6][col].setPiece(new Pawn(true));
        chessboard[1][col].setPiece(new Pawn(false));
    }

    chessboard[7][0].setPiece(new Rook(true));
    chessboard[7][7].setPiece(new Rook(true));
    chessboard[0][0].setPiece(new Rook(false));
    chessboard[0][7].setPiece(new Rook(false));
    

}

Board::~Board() {
}

Tile& Board::getTile(int row, int col) {
    return chessboard[row][col];
}