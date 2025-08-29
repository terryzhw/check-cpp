#include "King.h"

King::King(bool isWhite) : Piece(isWhite, true) {

}

King::~King() {

}

int King::getPieceType() const {
    return 6;
}