#include "Pawn.h"

Pawn::Pawn(bool isWhite) : Piece(isWhite, true) {
    hasMoved = false;
    passantVulnerable = false;
}

Pawn::~Pawn() {

}

int Pawn::getPieceType() const {
    return 1;
}

bool Pawn::getHasMoved() const {
    return hasMoved;
}

bool Pawn::getPassantVulnerable() const {
    return passantVulnerable;
}

void Pawn::setHasMoved(bool moved) {
    hasMoved = moved;
}

void Pawn::setPassantVulnerable(bool vulnerable) {
    passantVulnerable = vulnerable;
}


bool Pawn::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) {
    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }
    
    int direction;
    if (isWhite) {
        direction = -1;
    } else {
        direction = 1;
    }
    
    int rowDiff = toRow - fromRow;
    int colDiff = abs(toCol - fromCol);
    
    // regular movement
    if (fromCol == toCol) {
        if (rowDiff == direction) {
            return board.getTile(toRow, toCol).isEmpty();
        }
        else if (rowDiff == 2 * direction && !hasMoved) {
            return board.getTile(toRow, toCol).isEmpty() && board.getTile(fromRow + direction, fromCol).isEmpty();
        }
    }
    // capture 
    else if (colDiff == 1 && rowDiff == direction) {
        if (!board.getTile(toRow, toCol).isEmpty()) {
            Piece* targetPiece = board.getTile(toRow, toCol).getPiece();
            return targetPiece->getIsWhite() != isWhite;
        }
        //en passant
        else if (toCol == fromCol + 1 && fromCol + 1 < 8 && !board.getTile(fromRow, fromCol+1).isEmpty()) {
            Piece* targetPiece = board.getTile(fromRow, fromCol+1).getPiece();
            if (targetPiece->getPieceType() == 1 && targetPiece->getIsWhite() != isWhite) {
                Pawn* targetPawn = dynamic_cast<Pawn*>(targetPiece);
                return targetPawn->getPassantVulnerable();
            }
        }
        else if (toCol == fromCol - 1 && fromCol - 1 >= 0 && !board.getTile(fromRow, fromCol-1).isEmpty()) {
            Piece* targetPiece = board.getTile(fromRow, fromCol-1).getPiece();
            if (targetPiece->getPieceType() == 1 && targetPiece->getIsWhite() != isWhite) {
                Pawn* targetPawn = dynamic_cast<Pawn*>(targetPiece);
                return targetPawn->getPassantVulnerable();
            }
        }
    }

    
    return false;
}

bool Pawn::isPromoted(int toRow, Board& board) const {
    return (isWhite && toRow == 0) || (!isWhite && toRow == 7);
}