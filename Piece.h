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

    virtual int getPieceType() const = 0;
};

