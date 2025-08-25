#include "Game.h"
#include <QBrush>
#include <QColor>

Game::Game(QWidget* parent) : QWidget(parent) {
    setFixedSize(800, 800);
    setWindowTitle("Chess");
}

Game::~Game() {
    
}

void Game::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    
    int tileSize = 75;
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if ((row + col) % 2 == 0) {
                // light tiles
                painter.fillRect(col * tileSize, row * tileSize, tileSize, tileSize, QColor(177, 228, 185));
            } else {
                // dark tiles
                painter.fillRect(col * tileSize, row * tileSize, tileSize, tileSize, QColor(112, 162, 163));
            }
        }
    }
}