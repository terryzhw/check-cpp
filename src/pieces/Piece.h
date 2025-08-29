#pragma once

class Piece
{
protected:
    bool isWhite;
    bool isAlive;
public:
    Piece();
    Piece(bool isWhite, bool isAlive);
    virtual ~Piece();

    bool getIsWhite() const;
    bool getIsAlive() const;

    // 1 pawn, 2 bishop, 3 knight, 4 rook, 5 queen, 6 king
    virtual int getPieceType() const = 0;
};

