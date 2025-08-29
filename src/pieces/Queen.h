#include "Piece.h"

class Queen : public Piece
{
private:

public:
    Queen(bool isWhite);
    ~Queen();
    int getPieceType() const override;
};


