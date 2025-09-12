#include "Piece.h"
#include "../board/Board.h"

class Queen : public Piece
{
private:

public:
    Queen(bool isWhite);
    ~Queen();
    int getPieceType() const override;
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const;
};


