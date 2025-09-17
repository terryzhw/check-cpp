#pragma once
#include "Piece.h"
#include "../board/Board.h"

class Pawn : public Piece
{
private:
    bool hasMoved;
    bool passantVulnerable;
    
public:
    Pawn(bool isWhite);
    ~Pawn();

    int getPieceType() const override;
    bool getHasMoved() const;
    bool getPassantVulnerable() const;
    void setHasMoved(bool moved);
    void setPassantVulnerable(bool vulnerable);
    bool isPromoted(int toRow, Board& board) const;
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const;
    bool canAttack(int fromRow, int fromCol, int toRow, int toCol) const;
};

