#include "Tile.h"

Tile::Tile() {
    piece = nullptr;
}

Tile::~Tile() {
    if (piece != nullptr) {
        delete piece;
    }
}

Piece* Tile::getPiece() const {
    return piece;
}

void Tile::setPiece(Piece* newPiece){
    piece = newPiece;
}

bool Tile::isEmpty() const{
    return piece == nullptr;
}