#pragma once
#include "Piece.h"
#include "../board/Board.h"

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
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const;
};

