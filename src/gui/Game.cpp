#include "Game.h"
#include <QBrush>
#include <QColor>

Game::Game(QWidget* parent) : QWidget(parent) {
    setFixedSize(800, 800);
    setWindowTitle("Chess");
    selectedRow = -1;
    selectedCol = -1;
    pieceSelected = false;
    whoseTurn = false;
}

Game::~Game() {
    
}

void Game::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    
    int tileSize = 75;
    
    // drawing board
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 0) {
                // light tiles
                painter.fillRect(col * tileSize, row * tileSize, tileSize, tileSize, QColor(177, 228, 185));
            } else {
                // dark tiles
                painter.fillRect(col * tileSize, row * tileSize, tileSize, tileSize, QColor(112, 162, 163));
            }
            
            // highlight
            if (pieceSelected && row == selectedRow && col == selectedCol) {
                painter.fillRect(col * tileSize, row * tileSize, tileSize, tileSize, QColor(255, 255, 0, 128));
            }
        }
    }
    // drawing pieces
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (!board.getTile(row, col).isEmpty()) {
                Piece* piece = board.getTile(row, col).getPiece();
                if (piece->getPieceType() == 1) {
                  QPixmap pawnSprite;
                  if (piece->getIsWhite()) {
                      pawnSprite.load("../src/assets/w_pawn.png");
                  } else {
                      pawnSprite.load("../src/assets/b_pawn.png");
                  }
                  int pieceSize = tileSize - 5;  // Leave 5px margin
                  int x = col * tileSize + (tileSize - pieceSize) / 2;
                  int y = row * tileSize + (tileSize - pieceSize) / 2;
                  painter.drawPixmap(x, y, pieceSize, pieceSize, pawnSprite);
                }
                else if (piece->getPieceType() == 2) {
                  QPixmap bishopSprite;
                  if (piece->getIsWhite()) {
                      bishopSprite.load("../src/assets/w_bishop.png");
                  } else {
                      bishopSprite.load("../src/assets/b_bishop.png");
                  }
                  int pieceSize = tileSize - 5;  // Leave 5px margin
                  int x = col * tileSize + (tileSize - pieceSize) / 2;
                  int y = row * tileSize + (tileSize - pieceSize) / 2;
                  painter.drawPixmap(x, y, pieceSize, pieceSize, bishopSprite);
                }
                else if (piece->getPieceType() == 3) {
                  QPixmap knightSprite;
                  if (piece->getIsWhite()) {
                      knightSprite.load("../src/assets/w_knight.png");
                  } else {
                      knightSprite.load("../src/assets/b_knight.png");
                  }
                  int pieceSize = tileSize - 5;  // Leave 5px margin
                  int x = col * tileSize + (tileSize - pieceSize) / 2;
                  int y = row * tileSize + (tileSize - pieceSize) / 2;
                  painter.drawPixmap(x, y, pieceSize, pieceSize, knightSprite);
                }
                else if (piece->getPieceType() == 4) {
                  QPixmap rookSprite;
                  if (piece->getIsWhite()) {
                      rookSprite.load("../src/assets/w_rook.png");
                  } else {
                      rookSprite.load("../src/assets/b_rook.png");
                  }
                  int pieceSize = tileSize - 5;  // Leave 5px margin
                  int x = col * tileSize + (tileSize - pieceSize) / 2;
                  int y = row * tileSize + (tileSize - pieceSize) / 2;
                  painter.drawPixmap(x, y, pieceSize, pieceSize, rookSprite);
                }
                else if (piece->getPieceType() == 5) {
                  QPixmap queenSprite;
                  if (piece->getIsWhite()) {
                      queenSprite.load("../src/assets/w_queen.png");
                  } else {
                      queenSprite.load("../src/assets/b_queen.png");
                  }
                  int pieceSize = tileSize - 5;  // Leave 5px margin
                  int x = col * tileSize + (tileSize - pieceSize) / 2;
                  int y = row * tileSize + (tileSize - pieceSize) / 2;
                  painter.drawPixmap(x, y, pieceSize, pieceSize, queenSprite);
                }
                else if (piece->getPieceType() == 6) {
                  QPixmap kingSprite;
                  if (piece->getIsWhite()) {
                      kingSprite.load("../src/assets/w_king.png");
                  } else {
                      kingSprite.load("../src/assets/b_king.png");
                  }
                  int pieceSize = tileSize - 5;  // Leave 5px margin
                  int x = col * tileSize + (tileSize - pieceSize) / 2;
                  int y = row * tileSize + (tileSize - pieceSize) / 2;
                  painter.drawPixmap(x, y, pieceSize, pieceSize, kingSprite);
                }
            }
        }
    }
}

void Game::mousePressEvent(QMouseEvent* event) {
    int tileSize = 75;
    int col = event->position().x() / tileSize;
    int row = event->position().y() / tileSize;
    
    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        return;
    }
    
    if (!pieceSelected) {
        Piece* piece = board.getTile(row, col).getPiece();
        if (!board.getTile(row, col).isEmpty() && !whoseTurn && piece->getIsWhite()) {
            selectedRow = row;
            selectedCol = col;
            pieceSelected = true;
            update();
        }
        else if (!board.getTile(row, col).isEmpty() && whoseTurn && !piece->getIsWhite()) {
            selectedRow = row;
            selectedCol = col;
            pieceSelected = true;
            update();
        }

    } 
    else {
        if (board.makeMove(selectedRow, selectedCol, row, col)) {
            whoseTurn = !whoseTurn;
        }
        pieceSelected = false;
        update(); 
    }
}