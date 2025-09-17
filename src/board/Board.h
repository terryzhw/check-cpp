#pragma once
#include "Tile.h"
#include <vector>

class Board
{
private:
    std::vector<std::vector<Tile>> chessboard;
    int moves;
    int halfMove; 

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
    bool beKingCheck(int fromRow, int fromCol, int toRow, int toCol, bool kingColor);
    bool noLegalMoves(bool kingColor);
    bool isCheckmate(bool kingColor);
    bool isStalemate(bool kingColor);
    bool isFiftyMove() const;
    void gameState(bool pieceColor);

    
};

