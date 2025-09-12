#include "Piece.h"
#include "../board/Board.h"

class Knight : public Piece
{
private:

public:
    Knight(bool isWhite);
    ~Knight();
    int getPieceType() const override;
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const;
};

