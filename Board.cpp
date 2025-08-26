#include "Board.h"
#include <iostream>

Board::Board() {
    chessboard = std::vector<std::vector<Tile>>(8, std::vector<Tile>(8));
}

Board::~Board() {
}