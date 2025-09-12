#include "Piece.h"
#include "../board/Board.h"

class King : public Piece {
private:

public:
    King(bool isWhite);
    ~King();
    int getPieceType() const;
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const;
};


