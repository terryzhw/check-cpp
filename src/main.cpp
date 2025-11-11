#include "gui/Game.h"
#include "gui/Menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Menu* menu = new Menu();

    QObject::connect(menu, &Menu::startGame, [menu](bool isPlayerVsBot, int whiteBotDepth, int blackBotDepth) {
        menu->close();
        Game* game = new Game(isPlayerVsBot, whiteBotDepth, blackBotDepth);
        game->setAttribute(Qt::WA_DeleteOnClose);
        game->show();
    });

    menu->show();

    return app.exec();
}
