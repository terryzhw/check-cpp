#include "Bishop.h"

Bishop::Bishop(bool isWhite) : Piece(isWhite, true) {

}

Bishop::~Bishop() {

}

int Bishop::getPieceType() const {
    return 2;
}