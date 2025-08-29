#include "Piece.h"

Piece::Piece() {
    isWhite = true;
    isAlive = true;
}

Piece::~Piece() {
    
}

Piece::Piece(bool white, bool alive) {
    isWhite = white;
    isAlive = alive;
}

bool Piece::getIsWhite() const {
    return isWhite;
}
bool Piece::getIsAlive() const {
    return isAlive;
}