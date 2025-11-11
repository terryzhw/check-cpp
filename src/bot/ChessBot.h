#pragma once
#include "../board/Board.h"
#include <vector>
#include <utility>

struct Move {
    int fromRow, fromCol, toRow, toCol;
    int score;
    int promotionPiece;

    Move(int fRow, int fCol, int tRow, int tCol)
        : fromRow(fRow), fromCol(fCol), toRow(tRow), toCol(tCol), score(0), promotionPiece(0) {}
};

class ChessBot {
private:
    static const int PIECE_VALUES[7];
    static const int POSITION_BONUS[8][8];
    int searchDepth;

    int evaluateBoard(const Board& board, bool isWhite) const;
    int minimax(Board& board, int depth, int alpha, int beta, bool isMaximizingPlayer, bool botColor) const;
    std::vector<Move> generateMoves(const Board& board, bool isWhite) const;
    Board copyBoard(const Board& original) const;
    void restoreBoard(Board& target, const Board& source) const;

public:
    ChessBot(int depth = 3);
    Move getBestMove(Board& board, bool botColor) const;
    void setSearchDepth(int depth);
    int getSearchDepth() const;
};
