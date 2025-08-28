
#include <QWidget>
#include <QPainter>
#include "../board/Board.h"

class Game : public QWidget
{
private:
    Board board;
    
public:
    Game(QWidget* parent = nullptr);
    ~Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

protected:
    void paintEvent(QPaintEvent* event) override;
};
