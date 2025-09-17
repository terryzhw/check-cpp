#pragma once
#include "Tile.h"
#include <vector>

class Board
{
private:
    std::vector<std::vector<Tile>> chessboard;
    int moves; 

public:
    Board();
    ~Board();
    Tile& getTile(int row, int col);
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);
    int getMoves() const;
    void setMoves(int move);
    void whitePromote(int toRow, int toCol);
    void blackPromote(int toRow, int toCol);
    bool findKing(bool kingColor, int& kingRow, int& kingCol) const;
    bool kingCheck(bool kingColor);

    
};

