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

    return false;



}