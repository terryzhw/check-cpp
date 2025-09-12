#include "King.h"

King::King(bool isWhite) : Piece(isWhite, true) {

}

King::~King() {

}

int King::getPieceType() const {
    return 6;
}

bool King::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const {
    if (toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }

    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);

    if (rowDiff <= 1 && colDiff <= 1) {
        if (!board.getTile(toRow, toCol).isEmpty()) {
            Piece* targetPiece = board.getTile(toRow, toCol).getPiece();
            return targetPiece->getIsWhite() != isWhite;
        }
        return true;
    }

    return false;


}