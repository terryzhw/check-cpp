#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
    bool hasMoved;
    
public:
    Pawn(bool isWhite);
    ~Pawn();

    int getPieceType() const override;
    bool getHasMoved() const;
    void setHasMoved(bool moved);
};

