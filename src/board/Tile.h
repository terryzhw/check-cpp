#pragma once
#include "../pieces/Piece.h"

class Tile
{
private:
    Piece* piece;
public:
    Tile();
    ~Tile();
    Piece* getPiece() const;
    void setPiece(Piece* newPiece);
    bool isEmpty() const;


};
