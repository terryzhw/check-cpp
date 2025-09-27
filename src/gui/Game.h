
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QString>
#include "../board/Board.h"

class Game : public QWidget
{
private:
    Board board;
    int selectedRow;
    int selectedCol;
    bool pieceSelected;
    bool whoseTurn; // false white, true black
    QString statusMessage;
    
public:
    Game(QWidget* parent = nullptr);
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
};
