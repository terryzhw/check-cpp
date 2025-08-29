#include "Knight.h"

Knight::Knight(bool isWhite) : Piece(isWhite, true) {

}

Knight::~Knight() {

}

int Knight::getPieceType() const {
    return 3;
}