#pragma once
#include "Piece.h"
#include "../board/Board.h"

class Bishop : public Piece
{
private:

public:
    Bishop(bool isWhite);
    ~Bishop();
    int getPieceType() const override;
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const;

};

