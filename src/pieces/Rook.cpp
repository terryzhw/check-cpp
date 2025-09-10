#include "Rook.h"

Rook::Rook(bool isWhite) : Piece(isWhite, true) {

}

Rook::~Rook() {

}

int Rook::getPieceType() const {
    return 4;
}

bool Rook::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const {
    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (fromCol == toCol) {
        if (rowDiff < 0) {
            for (int i=fromRow-1; i>toRow; i--) {
                if (!board.getTile(i, fromCol).isEmpty()) {
                    return false;
                }
            }
        }
        else if (rowDiff > 0) {
            for (int i=fromRow+1; i<toRow; i++) {
                if (!board.getTile(i, fromCol).isEmpty()) {
                    return false;
                }
            }
        }
        if (!board.getTile(toRow, toCol).isEmpty()) {
            Piece* targetPiece = board.getTile(toRow, toCol).getPiece();
            return targetPiece->getIsWhite() != isWhite;
        }
        return board.getTile(toRow, toCol).isEmpty();
    }

    else if (fromRow == toRow) {
        if (colDiff < 0) {
            for (int i=fromCol-1; i>toCol; i--) {
                if (!board.getTile(fromRow, i).isEmpty()) {
                    return false;
                }
            }
        }
        else if (colDiff > 0) {
            for (int i=fromCol+1; i<toCol; i++) {
                if (!board.getTile(fromRow, i).isEmpty()) {
                    return false;
                }
            }
        }
        if (!board.getTile(toRow, toCol).isEmpty()) {
            Piece* targetPiece = board.getTile(toRow, toCol).getPiece();
            return targetPiece->getIsWhite() != isWhite;
        }
        return board.getTile(toRow, toCol).isEmpty();
    }


    return false;
}
