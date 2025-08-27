#include "Board.h"
#include "Pawn.h"
#include <iostream>

Board::Board() {
    chessboard = std::vector<std::vector<Tile>>(8, std::vector<Tile>(8));

    for (int col = 0; col < 8; col++) {
        chessboard[6][col].setPiece(new Pawn(true));
        chessboard[1][col].setPiece(new Pawn(false));
    }
}

Board::~Board() {
}

Tile& Board::getTile(int row, int col) {
    return chessboard[row][col];
}