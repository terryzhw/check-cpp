#include "Queen.h"

Queen::Queen(bool isWhite) : Piece(isWhite, true) {

}

Queen::~Queen() {

}

int Queen::getPieceType() const {
    return 5;
}

bool Queen::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const {
    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (fromCol == toCol && rowDiff != 0) {
        if (rowDiff < 0) {
            for (int i = fromRow - 1; i > toRow; i--) {
                if (!board.getTile(i, fromCol).isEmpty()) {
                    return false;
                }
            }
        } else {
            for (int i = fromRow + 1; i < toRow; i++) {
                if (!board.getTile(i, fromCol).isEmpty()) {
                    return false;
                }
            }
        }
    }
    else if (fromRow == toRow && colDiff != 0) {
        if (colDiff < 0) {
            for (int i = fromCol - 1; i > toCol; i--) {
                if (!board.getTile(fromRow, i).isEmpty()) {
                    return false;
                }
            }
        } else {
            for (int i = fromCol + 1; i < toCol; i++) {
                if (!board.getTile(fromRow, i).isEmpty()) {
                    return false;
                }
            }
        }
    }
    else if (abs(rowDiff) == abs(colDiff) && rowDiff != 0) {
        // up right
        if (rowDiff < 0 && colDiff > 0) {
            for (int i = 1; i < abs(rowDiff); i++) {
                int checkRow = fromRow - i;
                int checkCol = fromCol + i;
                if (!board.getTile(checkRow, checkCol).isEmpty()) {
                    return false;
                }
            }
        }
        // down right
        else if (rowDiff > 0 && colDiff > 0) {
            for (int i = 1; i < abs(rowDiff); i++) {
                int checkRow = fromRow + i;
                int checkCol = fromCol + i;
                if (!board.getTile(checkRow, checkCol).isEmpty()) {
                    return false;
                }
            }
        }
        // up left
        else if (rowDiff < 0 && colDiff < 0) {
            for (int i = 1; i < abs(rowDiff); i++) {
                int checkRow = fromRow - i;
                int checkCol = fromCol - i;
                if (!board.getTile(checkRow, checkCol).isEmpty()) {
                    return false;
                }
            }
        }
        // down left
        else if (rowDiff > 0 && colDiff < 0) {
            for (int i = 1; i < abs(rowDiff); i++) {
                int checkRow = fromRow + i;
                int checkCol = fromCol - i;
                if (!board.getTile(checkRow, checkCol).isEmpty()) {
                    return false;
                }
            }
        }
    }
    else {
        return false;
    }

    if (!board.getTile(toRow, toCol).isEmpty()) {
        Piece* targetPiece = board.getTile(toRow, toCol).getPiece();
        return targetPiece->getIsWhite() != isWhite;
    }
    
    return true;
}

