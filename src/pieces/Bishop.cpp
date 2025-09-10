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
        return true;
    }

    return false;

}