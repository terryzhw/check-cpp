#include "Pawn.h"

Pawn::Pawn(bool isWhite) : Piece(isWhite, true) {
    hasMoved = false;
}

Pawn::~Pawn() {

}

int Pawn::getPieceType() const {
    return 1;
}

bool Pawn::getHasMoved() const {
    return hasMoved;
}

void Pawn::setHasMoved(bool moved) {
    hasMoved = moved;
}