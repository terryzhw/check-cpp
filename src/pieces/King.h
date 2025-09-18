#include "Piece.h"
#include "../board/Board.h"

class King : public Piece {
private:
    bool hasMoved;
public:
    King(bool isWhite);
    ~King();
    int getPieceType() const;
    bool getHasMoved() const;
    void setHasMoved(bool moved);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Board& board) const;
};


