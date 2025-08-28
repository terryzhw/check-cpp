#pragma once
#include "Piece.h"

class Rook : public Piece
{
private:    

public:
    Rook(bool isWhite);
    ~Rook();
    int getPieceType() const override;
};
