#pragma once
#include "Piece.h"
#include "../board/Board.h"

class Rook : public Piece
{
private:    

public:
    Rook(bool isWhite);
    ~Rook();
    int getPieceType() const override;
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const;
};
