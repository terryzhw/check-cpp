#pragma once
#include "Tile.h"
#include <vector>

class Board
{
private:
    std::vector<std::vector<Tile>> chessboard;

public:
    Board();
    ~Board();
    Tile& getTile(int row, int col);
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);
    void whitePromote(int toRow, int toCol);
    void blackPromote(int toRow, int toCol);
    
};
