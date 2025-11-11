#pragma once

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT

private:
    QPushButton* playerVsBotButton;
    QPushButton* botVsBotButton;
    QSlider* whiteBotDepthSlider;
    QSlider* blackBotDepthSlider;
    QLabel* whiteBotDepthLabel;
    QLabel* blackBotDepthLabel;
    QLabel* titleLabel;

    int whiteBotDepth;
    int blackBotDepth;

private slots:
    void onPlayerVsBotClicked();
    void onBotVsBotClicked();
    void onWhiteBotDepthChanged(int value);
    void onBlackBotDepthChanged(int value);

signals:
    void startGame(bool isPlayerVsBot, int whiteBotDepth, int blackBotDepth);

public:
    Menu(QWidget* parent = nullptr);
    ~Menu();
};
