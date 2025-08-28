#include "Rook.h"

Rook::Rook(bool isWhite) : Piece(isWhite, true) {

}

Rook::~Rook() {

}

int Rook::getPieceType() const {
    return 4;
}
