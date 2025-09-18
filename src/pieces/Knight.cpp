#include "Knight.h"

Knight::Knight(bool isWhite) : Piece(isWhite, true) {

}

Knight::~Knight() {

}

int Knight::getPieceType() const {
    return 3;
}

bool Knight::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const {
    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }


    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);


    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        if (!board.getTile(toRow, toCol).isEmpty()) {
            Piece* targetPiece = board.getTile(toRow, toCol).getPiece();
            return targetPiece->getIsWhite() != isWhite;
        }
        return true;
    }

    return false;

}