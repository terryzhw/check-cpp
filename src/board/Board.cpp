#include "Board.h"
#include "../pieces/Pawn.h"
#include "../pieces/Bishop.h"
#include "../pieces/Knight.h"
#include "../pieces/Rook.h"
#include "../pieces/Queen.h"
#include "../pieces/King.h"
#include <iostream>

Board::Board() {
    chessboard = std::vector<std::vector<Tile>>(8, std::vector<Tile>(8));

    for (int col = 0; col < 8; col++) {
        chessboard[6][col].setPiece(new Pawn(true));
        chessboard[1][col].setPiece(new Pawn(false));
    }
    
    chessboard[7][2].setPiece(new Bishop(true));
    chessboard[7][5].setPiece(new Bishop(true));
    chessboard[0][2].setPiece(new Bishop(false));
    chessboard[0][5].setPiece(new Bishop(false));

    chessboard[7][1].setPiece(new Knight(true));
    chessboard[7][6].setPiece(new Knight(true));
    chessboard[0][1].setPiece(new Knight(false));
    chessboard[0][6].setPiece(new Knight(false));

    chessboard[7][0].setPiece(new Rook(true));
    chessboard[7][7].setPiece(new Rook(true));
    chessboard[0][0].setPiece(new Rook(false));
    chessboard[0][7].setPiece(new Rook(false));

    chessboard[7][3].setPiece(new Queen(true));
    chessboard[0][3].setPiece(new Queen(false));

    chessboard[7][4].setPiece(new King(true));
    chessboard[0][4].setPiece(new King(false));

    moves = 0;
}

Board::~Board() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (!chessboard[row][col].isEmpty()) {
                delete chessboard[row][col].getPiece();
            }
        }
    }
}

Tile& Board::getTile(int row, int col) {
    return chessboard[row][col];
}

int Board::getMoves() const {
    return moves;
}

void Board::setMoves(int move) {
    moves = move;
}


bool Board::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
        toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }
    
    if (chessboard[fromRow][fromCol].isEmpty()) {
        return false;
    }

    // reset en passant vulnerability
    bool movingPieceColor = chessboard[fromRow][fromCol].getPiece()->getIsWhite();
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (!chessboard[row][col].isEmpty() && chessboard[row][col].getPiece()->getPieceType() == 1) {
                Pawn* pawn = dynamic_cast<Pawn*>(chessboard[row][col].getPiece());
                if (pawn->getIsWhite() == movingPieceColor) {
                    pawn->setPassantVulnerable(false);
                }
            }
        }
    }
    
    Piece* piece = chessboard[fromRow][fromCol].getPiece();
    
    if (piece->getPieceType() == 1) {
        Pawn* pawn = dynamic_cast<Pawn*>(piece);
        if (pawn->isValidMove(fromRow, fromCol, toRow, toCol, *this)) {
            
            if (!chessboard[toRow][toCol].isEmpty()) {
                delete chessboard[toRow][toCol].getPiece();
            }

            else if (abs(toCol - fromCol) == 1 && chessboard[toRow][toCol].isEmpty()) {
                if (toCol == fromCol + 1 && fromCol + 1 < 8 && !chessboard[fromRow][fromCol+1].isEmpty()){
                    Piece* capturedPiece = chessboard[fromRow][fromCol+1].getPiece();
                    if (capturedPiece->getPieceType() == 1) {
                        Pawn* capturedPawn = dynamic_cast<Pawn*>(capturedPiece);
                        if (capturedPawn->getPassantVulnerable()) {
                            delete chessboard[fromRow][fromCol+1].getPiece();
                        }
                    }
                }
                else if (toCol == fromCol - 1 && fromCol - 1 >= 0 && !chessboard[fromRow][fromCol-1].isEmpty()){
                    Piece* capturedPiece = chessboard[fromRow][fromCol-1].getPiece();
                    if (capturedPiece->getPieceType() == 1) {
                        Pawn* capturedPawn = dynamic_cast<Pawn*>(capturedPiece);
                        if (capturedPawn->getPassantVulnerable()) {
                            delete chessboard[fromRow][fromCol-1].getPiece();
                            chessboard[fromRow][fromCol-1].setPiece(nullptr);
                        }
                    }
                }
            }
            
            chessboard[toRow][toCol].setPiece(piece);
            chessboard[fromRow][fromCol].setPiece(nullptr);
            pawn->setHasMoved(true);
            
            // en passant vulnerability flag

            if (abs(toRow - fromRow) == 2) {
                pawn->setPassantVulnerable(true);
            }


            if (pawn->isPromoted(toRow, *this)) {
                if (pawn->getIsWhite()) {
                    delete chessboard[toRow][toCol].getPiece();
                    chessboard[toRow][toCol].setPiece(nullptr);
                    whitePromote(toRow, toCol);
                }
                else {
                    delete chessboard[toRow][toCol].getPiece();
                    chessboard[toRow][toCol].setPiece(nullptr);
                    blackPromote(toRow, toCol);
                }
                
            }
            return true;
        }
    }

    else if (piece->getPieceType() == 2) {
        Bishop* bishop = dynamic_cast<Bishop*>(piece);

        if (bishop->isValidMove(fromRow, fromCol, toRow, toCol, *this)) {
            if (!chessboard[toRow][toCol].isEmpty()) {
                delete chessboard[toRow][toCol].getPiece();
            }
            chessboard[toRow][toCol].setPiece(piece);
            chessboard[fromRow][fromCol].setPiece(nullptr);
            return true;
        }
    }
    else if (piece->getPieceType() == 3) {
        Knight* knight = dynamic_cast<Knight*>(piece);
        if (knight->isValidMove(fromRow, fromCol, toRow, toCol, *this)) {
            if (!chessboard[toRow][toCol].isEmpty()) {
                delete chessboard[toRow][toCol].getPiece();
            }
            chessboard[toRow][toCol].setPiece(piece);
            chessboard[fromRow][fromCol].setPiece(nullptr);
            return true;
        }
    }
    else if (piece->getPieceType() == 4) {
        Rook* rook = dynamic_cast<Rook*>(piece);
        if (rook->isValidMove(fromRow, fromCol, toRow, toCol, *this)) {
            if (!chessboard[toRow][toCol].isEmpty()) {
                delete chessboard[toRow][toCol].getPiece();
            }
            chessboard[toRow][toCol].setPiece(piece);
            chessboard[fromRow][fromCol].setPiece(nullptr);

            rook->setHasMoved(true);
            return true;
        }
    }
    else if (piece->getPieceType() == 5) {
        Queen* queen = dynamic_cast<Queen*>(piece);
        if (queen->isValidMove(fromRow, fromCol, toRow, toCol, *this)) {
            if (!chessboard[toRow][toCol].isEmpty()) {
                delete chessboard[toRow][toCol].getPiece();
            }
            chessboard[toRow][toCol].setPiece(piece);
            chessboard[fromRow][fromCol].setPiece(nullptr);
            return true;
        }
    }
    else if (piece->getPieceType() == 6) {
        King* king = dynamic_cast<King*>(piece);
        if (king->isValidMove(fromRow, fromCol, toRow, toCol, *this)) {
            int colDiff = toCol - fromCol;
            
            if (!king->getHasMoved() && abs(colDiff) == 2) {
                // king side 
                if (colDiff == 2) {
                    Piece* rook = chessboard[fromRow][7].getPiece();
                    chessboard[fromRow][5].setPiece(rook);
                    chessboard[fromRow][7].setPiece(nullptr);
                    
                    Rook* castleRook = dynamic_cast<Rook*>(rook);
                    castleRook->setHasMoved(true);
                }
                // queen side
                else if (colDiff == -2) {
                    Piece* rook = chessboard[fromRow][0].getPiece();
                    chessboard[fromRow][3].setPiece(rook);
                    chessboard[fromRow][0].setPiece(nullptr);
                    
                    Rook* castleRook = dynamic_cast<Rook*>(rook);
                    castleRook->setHasMoved(true);
                }
            }
            
            if (!chessboard[toRow][toCol].isEmpty()) {
                delete chessboard[toRow][toCol].getPiece();
            }
            chessboard[toRow][toCol].setPiece(piece);
            chessboard[fromRow][fromCol].setPiece(nullptr);

            king->setHasMoved(true);
            return true;
        }
    }
    
    return false;
}

void Board::whitePromote(int toRow, int toCol) {

    int pieceNumber;

    std::cout << "Promotion" << std::endl;
    std::cout << "1: Queen" << std::endl;
    std::cout << "2: Rook" << std::endl;
    std::cout << "3: Bishop" << std::endl;
    std::cout << "4: Knight" << std::endl;
    std::cout << "Enter the piece number (1-4): ";
    std::cin >> pieceNumber;
    

    while (true) {
        if (pieceNumber == 1) {
            chessboard[toRow][toCol].setPiece(new Queen(true));
            return;
        }
        else if (pieceNumber == 2) {
            chessboard[toRow][toCol].setPiece(new Rook(true));
            return;
        }
        else if (pieceNumber == 3) {
            chessboard[toRow][toCol].setPiece(new Bishop(true));
            return;
        }
        else if (pieceNumber == 4) {
            chessboard[toRow][toCol].setPiece(new Knight(true));
            return;
        }
        else {
            std::cout << "Error: invalid input" << std::endl;
            std::cout << "Enter the piece number (1-4): ";
            std::cin >> pieceNumber;
        }
    }

}

void Board::blackPromote(int toRow, int toCol) {

    int pieceNumber;

    std::cout << "Promotion" << std::endl;
    std::cout << "1: Queen" << std::endl;
    std::cout << "2: Rook" << std::endl;
    std::cout << "3: Bishop" << std::endl;
    std::cout << "4: Knight" << std::endl;
    std::cout << "Enter the piece number (1-4): ";
    std::cin >> pieceNumber;
    

    while (true) {
        if (pieceNumber == 1) {
            chessboard[toRow][toCol].setPiece(new Queen(false));
            return;
        }
        else if (pieceNumber == 2) {
            chessboard[toRow][toCol].setPiece(new Rook(false));
            return;
        }
        else if (pieceNumber == 3) {
            chessboard[toRow][toCol].setPiece(new Bishop(false));
            return;
        }
        else if (pieceNumber == 4) {
            chessboard[toRow][toCol].setPiece(new Knight(false));
            return;
        }
        else {
            std::cout << "Error: invalid input" << std::endl;
            std::cout << "Enter the piece number (1-4): ";
            std::cin >> pieceNumber;
        }
    }

}

bool Board::findKing(bool kingColor, int& kingRow, int& kingCol) const{
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (!chessboard[row][col].isEmpty()) {
                Piece* piece = chessboard[row][col].getPiece();
                if (piece->getPieceType() == 6 && piece->getIsWhite() == kingColor) {
                    kingRow = row;
                    kingCol = col;
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::kingCheck(bool kingColor) {
    int kingRow = 0;
    int kingCol = 0;

    if (!findKing(kingColor, kingRow, kingCol)) {
        return false;
    }

    for (int row=0; row<8; row++) {
        for (int col=0; col<8; col++) {
            if (!chessboard[row][col].isEmpty()) {
                Piece* piece = chessboard[row][col].getPiece();
                if (piece->getIsWhite() != kingColor) {
                    if (piece->getPieceType() == 1) {
                        Pawn* pawn = dynamic_cast<Pawn*>(piece);
                        if (pawn->isValidMove(row, col, kingRow, kingCol, *this)) {
                            return true;
                        }
                    }
                    else if (piece->getPieceType() == 2) {
                        Bishop* bishop= dynamic_cast<Bishop*>(piece);
                        if (bishop->isValidMove(row, col, kingRow, kingCol, *this)) {
                            return true;
                        }
                    }
                    else if (piece->getPieceType() == 3) {
                        Knight* knight = dynamic_cast<Knight*>(piece);
                        if (knight->isValidMove(row, col, kingRow, kingCol, *this)) {
                            return true;
                        }
                    }
                    else if (piece->getPieceType() == 4) {
                        Rook* rook = dynamic_cast<Rook*>(piece);
                        if (rook->isValidMove(row, col, kingRow, kingCol, *this)) {
                            return true;
                        }
                    }
                    else if (piece->getPieceType() == 5) {
                        Queen* queen = dynamic_cast<Queen*>(piece);
                        if (queen->isValidMove(row, col, kingRow, kingCol, *this)) {
                            return true;
                        }
                    }
                    else if (piece->getPieceType() == 6) {
                        King* king = dynamic_cast<King*>(piece);
                        if (king->isValidMove(row, col, kingRow, kingCol, *this)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
