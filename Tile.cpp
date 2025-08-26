#include "Tile.h"

Tile::Tile() {
    sideOccupied = 0;
    pieceOccupied = 0;
}

Tile::~Tile() {

}

int Tile::getSideOccupied() const {
    return sideOccupied;
}

int Tile::getPieceOccupied() const {
    return pieceOccupied;
}