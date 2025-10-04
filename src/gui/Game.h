
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QString>
#include <QTimer>
#include "../board/Board.h"
#include "../bot/ChessBot.h"

class Game : public QWidget
{
    Q_OBJECT

private:
    Board board;
    ChessBot bot;
    int selectedRow;
    int selectedCol;
    bool pieceSelected;
    bool whoseTurn; // false white, true black
    QString statusMessage;
    QTimer* botTimer;
    
public:
    Game(QWidget* parent = nullptr);
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private slots:
    void makeBotMove();
};
