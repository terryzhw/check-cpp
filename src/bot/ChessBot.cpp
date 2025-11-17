#include "ChessBot.h"
#include "../pieces/Pawn.h"
#include "../pieces/Bishop.h"
#include "../pieces/Knight.h"
#include "../pieces/Rook.h"
#include "../pieces/Queen.h"
#include "../pieces/King.h"
#include <algorithm>
#include <climits>

const int ChessBot::PIECE_VALUES[7] = {0, 100, 330, 320, 500, 900, 20000};

const int ChessBot::POSITION_BONUS[8][8] = {
    {-20, -10, -10, -10, -10, -10, -10, -20},
    {-10,   0,   0,   0,   0,   0,   0, -10},
    {-10,   0,   5,  10,  10,   5,   0, -10},
    {-10,   5,   5,  10,  10,   5,   5, -10},
    {-10,   0,  10,  10,  10,  10,   0, -10},
    {-10,  10,  10,  10,  10,  10,  10, -10},
    {-10,   5,   0,   0,   0,   0,   5, -10},
    {-20, -10, -10, -10, -10, -10, -10, -20}
};

ChessBot::ChessBot(int depth) : searchDepth(depth) {}

int ChessBot::evaluateBoard(const Board& board, bool isWhite) const {
    int score = 0;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Board& mutableBoard = const_cast<Board&>(board);
            if (!mutableBoard.getTile(row, col).isEmpty()) {
                Piece* piece = mutableBoard.getTile(row, col).getPiece();
                int pieceValue = PIECE_VALUES[piece->getPieceType()];
                int positionBonus = POSITION_BONUS[row][col];

                if (piece->getIsWhite() == isWhite) {
                    score += pieceValue + positionBonus;
                } else {
                    score -= pieceValue + positionBonus;
                }
            }
        }
    }

    return score;
}

std::vector<Move> ChessBot::generateMoves(const Board& board, bool isWhite) const {
    std::vector<Move> moves;

    for (int fromRow = 0; fromRow < 8; fromRow++) {
        for (int fromCol = 0; fromCol < 8; fromCol++) {
            Board& mutableBoard = const_cast<Board&>(board);
            if (!mutableBoard.getTile(fromRow, fromCol).isEmpty()) {
                Piece* piece = mutableBoard.getTile(fromRow, fromCol).getPiece();

                if (piece->getIsWhite() == isWhite) {
                    for (int toRow = 0; toRow < 8; toRow++) {
                        for (int toCol = 0; toCol < 8; toCol++) {
                            bool isValidMove = false;

                            switch (piece->getPieceType()) {
                                case 1: {
                                    Pawn* pawn = dynamic_cast<Pawn*>(piece);
                                    if (pawn) {
                                        isValidMove = pawn->isValidMove(fromRow, fromCol, toRow, toCol, mutableBoard);
                                    }
                                    break;
                                }
                                case 2: {
                                    Bishop* bishop = dynamic_cast<Bishop*>(piece);
                                    if (bishop) {
                                        isValidMove = bishop->isValidMove(fromRow, fromCol, toRow, toCol, mutableBoard);
                                    }
                                    break;
                                }
                                case 3: {
                                    Knight* knight = dynamic_cast<Knight*>(piece);
                                    if (knight) {
                                        isValidMove = knight->isValidMove(fromRow, fromCol, toRow, toCol, mutableBoard);
                                    }
                                    break;
                                }
                                case 4: {
                                    Rook* rook = dynamic_cast<Rook*>(piece);
                                    if (rook) {
                                        isValidMove = rook->isValidMove(fromRow, fromCol, toRow, toCol, mutableBoard);
                                    }
                                    break;
                                }
                                case 5: {
                                    Queen* queen = dynamic_cast<Queen*>(piece);
                                    if (queen) {
                                        isValidMove = queen->isValidMove(fromRow, fromCol, toRow, toCol, mutableBoard);
                                    }
                                    break;
                                }
                                case 6: {
                                    King* king = dynamic_cast<King*>(piece);
                                    if (king) {
                                        isValidMove = king->isValidMove(fromRow, fromCol, toRow, toCol, mutableBoard);
                                    }
                                    break;
                                }
                            }

                            if (isValidMove && !mutableBoard.beKingCheck(fromRow, fromCol, toRow, toCol, isWhite)) {
                                moves.push_back(Move(fromRow, fromCol, toRow, toCol));
                            }
                        }
                    }
                }
            }
        }
    }

    return moves;
}

Board ChessBot::copyBoard(const Board& original) const {
    Board copy;

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Board& mutableOriginal = const_cast<Board&>(original);
            if (!mutableOriginal.getTile(row, col).isEmpty()) {
                Piece* originalPiece = mutableOriginal.getTile(row, col).getPiece();
                Piece* newPiece = nullptr;

                switch (originalPiece->getPieceType()) {
                    case 1:
                        newPiece = new Pawn(originalPiece->getIsWhite());
                        break;
                    case 2:
                        newPiece = new Bishop(originalPiece->getIsWhite());
                        break;
                    case 3:
                        newPiece = new Knight(originalPiece->getIsWhite());
                        break;
                    case 4:
                        newPiece = new Rook(originalPiece->getIsWhite());
                        break;
                    case 5:
                        newPiece = new Queen(originalPiece->getIsWhite());
                        break;
                    case 6:
                        newPiece = new King(originalPiece->getIsWhite());
                        break;
                }

                copy.getTile(row, col).setPiece(newPiece);
            }
        }
    }

    copy.setMoves(original.getMoves());
    return copy;
}

int ChessBot::minimax(Board& board, int depth, int alpha, int beta, bool isMaximizingPlayer, bool botColor) const {
    if (depth == 0 || board.isGameOver(botColor)) {
        return evaluateBoard(board, botColor);
    }

    std::vector<Move> moves = generateMoves(board, isMaximizingPlayer ? botColor : !botColor);

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;

        for (const Move& move : moves) {
            Tile& fromTile = board.getTile(move.fromRow, move.fromCol);
            Tile& toTile = board.getTile(move.toRow, move.toCol);

            Piece* fromPiece = fromTile.getPiece();
            Piece* capturedPiece = toTile.getPiece();

            toTile.setPiece(fromPiece);
            fromTile.setPiece(nullptr);

            int eval = minimax(board, depth - 1, alpha, beta, false, botColor);

            fromTile.setPiece(fromPiece);
            toTile.setPiece(capturedPiece);

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);

            if (beta <= alpha) {
                break;
            }
        }

        return maxEval;
    } else {
        int minEval = INT_MAX;

        for (const Move& move : moves) {
            Tile& fromTile = board.getTile(move.fromRow, move.fromCol);
            Tile& toTile = board.getTile(move.toRow, move.toCol);

            Piece* fromPiece = fromTile.getPiece();
            Piece* capturedPiece = toTile.getPiece();

            toTile.setPiece(fromPiece);
            fromTile.setPiece(nullptr);

            int eval = minimax(board, depth - 1, alpha, beta, true, botColor);

            fromTile.setPiece(fromPiece);
            toTile.setPiece(capturedPiece);

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);

            if (beta <= alpha) {
                break;
            }
        }

        return minEval;
    }
}

Move ChessBot::getBestMove(Board& board, bool botColor) const {
    std::vector<Move> moves = generateMoves(board, botColor);

    if (moves.empty()) {
        return Move(-1, -1, -1, -1);
    }

    Move bestMove = moves[0];
    int bestScore = INT_MIN;

    for (Move& move : moves) {
        Tile& fromTile = board.getTile(move.fromRow, move.fromCol);
        Tile& toTile = board.getTile(move.toRow, move.toCol);

        Piece* fromPiece = fromTile.getPiece();
        Piece* capturedPiece = toTile.getPiece();

        toTile.setPiece(fromPiece);
        fromTile.setPiece(nullptr);

        int score = minimax(board, searchDepth - 1, INT_MIN, INT_MAX, false, botColor);

        fromTile.setPiece(fromPiece);
        toTile.setPiece(capturedPiece);

        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }

        move.score = score;
    }

    return bestMove;
}

void ChessBot::setSearchDepth(int depth) {
    searchDepth = depth;
}

int ChessBot::getSearchDepth() const {
    return searchDepth;
}
