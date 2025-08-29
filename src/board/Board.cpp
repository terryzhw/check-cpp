#include "Board.h"
#include "../pieces/Pawn.h"
#include "../pieces/Bishop.h"
#include "../pieces/Knight.h"
#include "../pieces/Rook.h"
#include "../pieces/Queen.h"
#include "../pieces/King.h"
#include <iostream>

Board::Board() {
    chessboard = std::vector<std::vector<Tile>>(8, std::vector<Tile>(8));

    for (int col = 0; col < 8; col++) {
        chessboard[6][col].setPiece(new Pawn(true));
        chessboard[1][col].setPiece(new Pawn(false));
    }
    
    chessboard[7][2].setPiece(new Bishop(true));
    chessboard[7][5].setPiece(new Bishop(true));
    chessboard[0][2].setPiece(new Bishop(false));
    chessboard[0][5].setPiece(new Bishop(false));

    chessboard[7][1].setPiece(new Knight(true));
    chessboard[7][6].setPiece(new Knight(true));
    chessboard[0][1].setPiece(new Knight(false));
    chessboard[0][6].setPiece(new Knight(false));

    chessboard[7][0].setPiece(new Rook(true));
    chessboard[7][7].setPiece(new Rook(true));
    chessboard[0][0].setPiece(new Rook(false));
    chessboard[0][7].setPiece(new Rook(false));

    chessboard[7][3].setPiece(new Queen(true));
    chessboard[0][3].setPiece(new Queen(false));

    chessboard[7][4].setPiece(new King(true));
    chessboard[0][4].setPiece(new King(false));


}

Board::~Board() {
}

Tile& Board::getTile(int row, int col) {
    return chessboard[row][col];
}

bool Board::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
        toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }
    
    if (chessboard[fromRow][fromCol].isEmpty()) {
        return false;
    }
    
    Piece* piece = chessboard[fromRow][fromCol].getPiece();
    
    if (piece->getPieceType() == 1) {
        Pawn* pawn = static_cast<Pawn*>(piece);
        if (pawn->isValidMove(fromRow, fromCol, toRow, toCol, *this)) {
            chessboard[toRow][toCol].setPiece(piece);
            chessboard[fromRow][fromCol].setPiece(nullptr);
            pawn->setHasMoved(true);
            return true;
        }
    }
    
    return false;
}