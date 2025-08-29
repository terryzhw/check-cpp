#include "Queen.h"

Queen::Queen(bool isWhite) : Piece(isWhite, true) {

}

Queen::~Queen() {

}

int Queen::getPieceType() const {
    return 5;
}