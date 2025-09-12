#include "Bishop.h"

Bishop::Bishop(bool isWhite) : Piece(isWhite, true) {

}

Bishop::~Bishop() {

}

int Bishop::getPieceType() const {
    return 2;
}

bool Bishop ::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const {
    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }

    int rowDiff = toRow - fromRow;
    int colDiff = toCol - fromCol;

    if (abs(rowDiff) == abs(colDiff)) {
        // up right
        if (rowDiff < 0 && colDiff > 0) {
            for (int i=1;i<abs(rowDiff); i++) {
                int checkRow = fromRow - i;
                int checkCol = fromCol + i;
                if (!board.getTile(checkRow, checkCol).isEmpty()) {
                    return false;
                }
            }
        }
        // down right
        else if (rowDiff > 0 && colDiff > 0) {
            for (int i=1;i<abs(rowDiff); i++) {
                int checkRow = fromRow + i;
                int checkCol = fromCol + i;
                if (!board.getTile(checkRow, checkCol).isEmpty()) {
                    return false;
                }
            }
        }
        // up left
        else if (rowDiff < 0 && colDiff < 0) {
            for (int i=1;i<abs(rowDiff); i++) {
                int checkRow = fromRow - i;
                int checkCol = fromCol - i;
                if (!board.getTile(checkRow, checkCol).isEmpty()) {
                    return false;
                }
            }
        }
        // down left
        else if (rowDiff > 0 && colDiff < 0) {
            for (int i=1;i<abs(rowDiff); i++) {
                int checkRow = fromRow + i;
                int checkCol = fromCol - i;
                if (!board.getTile(checkRow, checkCol).isEmpty()) {
                    return false;
                }
            }
        }
        
        if (!board.getTile(toRow, toCol).isEmpty()) {
            Piece* targetPiece = board.getTile(toRow, toCol).getPiece();
            return targetPiece->getIsWhite() != isWhite;
        }
        return true;
    }

    return false;

}