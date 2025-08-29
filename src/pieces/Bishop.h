#pragma once
#include "Piece.h"

class Bishop : public Piece
{
private:

public:
    Bishop(bool isWhite);
    ~Bishop();
    int getPieceType() const override;
};

