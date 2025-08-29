#include "Piece.h"

class Knight : public Piece
{
private:

public:
    Knight(bool isWhite);
    ~Knight();
    int getPieceType() const override;
};

