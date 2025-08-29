#include "Piece.h"

class King : public Piece {
private:

public:
    King(bool isWhite);
    ~King();
    int getPieceType() const;
};


