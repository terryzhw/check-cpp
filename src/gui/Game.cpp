#include "Game.h"
#include <QBrush>
#include <QColor>
#include <iostream>

Game::Game(QWidget* parent) : QWidget(parent), bot(5) {
    setFixedSize(800, 850);
    setWindowTitle("Chess vs Bot");
    selectedRow = -1;
    selectedCol = -1;
    pieceSelected = false;
    whoseTurn = false;
    statusMessage = "White to move";

    botTimer = new QTimer(this);
    botTimer->setSingleShot(true);
    connect(botTimer, &QTimer::timeout, this, &Game::makeBotMove);
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
                  int pieceSize = tileSize - 10;
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
                  int pieceSize = tileSize - 10; 
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
                  int pieceSize = tileSize - 10;  
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
                  int pieceSize = tileSize - 10;  // Leave 5px margin
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
                  int pieceSize = tileSize - 10;  
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
                  int pieceSize = tileSize - 10;  
                  int x = col * tileSize + (tileSize - pieceSize) / 2;
                  int y = row * tileSize + (tileSize - pieceSize) / 2;
                  painter.drawPixmap(x, y, pieceSize, pieceSize, kingSprite);
                }
            }
        }
    }

    if (!statusMessage.isEmpty()) {
        painter.setPen(QColor(255, 0, 0));
        QFont font = painter.font();
        font.setPointSize(14);
        font.setBold(true);
        painter.setFont(font);

        QRect textRect(0, 600, 800, 50);
        painter.drawText(textRect, Qt::AlignCenter, statusMessage);
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
        if (!board.getTile(row, col).isEmpty() && !whoseTurn) {
            Piece* piece = board.getTile(row, col).getPiece();
            if (piece && piece->getIsWhite()) {
                selectedRow = row;
                selectedCol = col;
                pieceSelected = true;
                update();
            }
        }
    }
    // switching turns
    else {
        if (board.makeMove(selectedRow, selectedCol, row, col)) {
            whoseTurn = !whoseTurn;

            std::string gameMessage = board.gameState(whoseTurn);

            // game over popup
            if (board.isGameOver(whoseTurn)) {
                QMessageBox::information(this, "Game Over", QString::fromStdString(gameMessage));
                statusMessage = QString::fromStdString(gameMessage);
            }
            else if (!gameMessage.empty()) {
                statusMessage = QString::fromStdString(gameMessage);
            }
            else {
                if (whoseTurn) {
                    statusMessage = "Bot thinking...";
                    update();
                    botTimer->start(1000);
                }
                else {
                    statusMessage = "White to move";
                }
            }
        }
        pieceSelected = false;
        update();
    }
}

void Game::makeBotMove() {
    if (!whoseTurn) return;

    Move botMove = bot.getBestMove(board, false);

    if (botMove.fromRow == -1) {
        statusMessage = "Bot has no legal moves";
        return;
    }

    if (board.makeMove(botMove.fromRow, botMove.fromCol, botMove.toRow, botMove.toCol)) {
        if (botMove.promotionPiece > 0 && !board.getTile(botMove.toRow, botMove.toCol).isEmpty()) {
            Piece* piece = board.getTile(botMove.toRow, botMove.toCol).getPiece();
            if (piece && piece->getPieceType() == 1) {
                delete piece;
                board.getTile(botMove.toRow, botMove.toCol).setPiece(nullptr);
                board.autoPromote(botMove.toRow, botMove.toCol, false, botMove.promotionPiece);
            }
        }

        whoseTurn = !whoseTurn;

        std::string gameMessage = board.gameState(whoseTurn);

        if (board.isGameOver(whoseTurn)) {
            QMessageBox::information(this, "Game Over", QString::fromStdString(gameMessage));
            statusMessage = QString::fromStdString(gameMessage);
        }
        else if (!gameMessage.empty()) {
            statusMessage = QString::fromStdString(gameMessage);
        }
        else {
            statusMessage = "White to move";
        }
    }

    update();
}
