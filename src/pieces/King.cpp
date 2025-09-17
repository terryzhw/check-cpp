#include "King.h"
#include "Rook.h"
#include <iostream>


King::King(bool isWhite) : Piece(isWhite, true) {
    hasMoved = false;
}

King::~King() {
    hasMoved = false;
}

int King::getPieceType() const {
    return 6;
}

bool King::getHasMoved() const {
    return hasMoved;
}

void King::setHasMoved(bool moved) {
    hasMoved = moved;
}

bool King::getIsChecked() const {
    return isChecked;
}

void King::setIsChecked(bool check) {
    isChecked = check;
}


bool King::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const {
    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (abs(rowDiff) <= 1 && abs(colDiff) <= 1) {
        if (!board.getTile(toRow, toCol).isEmpty()) {
            Piece* targetPiece = board.getTile(toRow, toCol).getPiece();
            return targetPiece->getIsWhite() != isWhite;
        }
        return true;
    }

    // king side
    else if (!hasMoved && rowDiff == 0 && colDiff == 2) {
        if (board.getTile(toRow, toCol).isEmpty() && board.getTile(toRow, toCol-1).isEmpty()) {
            if (!board.getTile(toRow, toCol+1).isEmpty()) {
                Piece* targetPiece = board.getTile(toRow, toCol+1).getPiece();
                if (targetPiece->getPieceType() == 4 && targetPiece->getIsWhite() == isWhite) {
                    Rook* targetRook = dynamic_cast<Rook*>(targetPiece);
                    if (!targetRook->getHasMoved()) {
                        if (board.kingCheck(isWhite)) {
                            return false;
                        }
                        if (board.beKingCheck(fromRow, fromCol, fromRow, fromCol + 1, isWhite)) {
                            return false;
                        }
                        if (board.beKingCheck(fromRow, fromCol, toRow, toCol, isWhite)) {
                            return false;
                        }
                        return true;
                    }
                }
            }
        }
    }

    // queen side
    else if (!hasMoved && rowDiff == 0 && colDiff == -2) {
        if (board.getTile(toRow, toCol).isEmpty() && board.getTile(toRow, toCol+1).isEmpty() && board.getTile(toRow, toCol-1).isEmpty()) {
            if (!board.getTile(toRow, toCol-2).isEmpty()) {
                Piece* targetPiece = board.getTile(toRow, toCol-2).getPiece();
                if (targetPiece->getPieceType() == 4 && targetPiece->getIsWhite() == isWhite) {
                    Rook* targetRook = dynamic_cast<Rook*>(targetPiece);
                    if (!targetRook->getHasMoved()) {
                        if (board.kingCheck(isWhite)) {
                            return false;
                        }
                        if (board.beKingCheck(fromRow, fromCol, fromRow, fromCol - 1, isWhite)) {
                            return false;
                        }
                        if (board.beKingCheck(fromRow, fromCol, toRow, toCol, isWhite)) {
                            return false;
                        }
                        return true;
                    }
                }
            }
        }
    }

    return false;


}