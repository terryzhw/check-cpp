#include "Menu.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

Menu::Menu(QWidget* parent) : QWidget(parent) {
    setFixedSize(400, 500);
    setWindowTitle("Menu");

    whiteBotDepth = 3;
    blackBotDepth = 3;

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    titleLabel = new QLabel("CheckCPP", this);
    QFont titleFont;
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    mainLayout->addSpacing(20);

    QLabel* gameModeLabel = new QLabel("Select Game Mode:", this);
    QFont sectionFont;
    sectionFont.setPointSize(14);
    sectionFont.setBold(true);
    gameModeLabel->setFont(sectionFont);
    mainLayout->addWidget(gameModeLabel);

    playerVsBotButton = new QPushButton("Player vs Bot", this);
    playerVsBotButton->setMinimumHeight(50);
    QFont buttonFont;
    buttonFont.setPointSize(12);
    playerVsBotButton->setFont(buttonFont);
    mainLayout->addWidget(playerVsBotButton);

    botVsBotButton = new QPushButton("Bot vs Bot", this);
    botVsBotButton->setMinimumHeight(50);
    botVsBotButton->setFont(buttonFont);
    mainLayout->addWidget(botVsBotButton);

    mainLayout->addSpacing(20);

    QLabel* whiteBotLabel = new QLabel("White Bot Depth:", this);
    whiteBotLabel->setFont(sectionFont);
    mainLayout->addWidget(whiteBotLabel);

    QHBoxLayout* whiteSliderLayout = new QHBoxLayout();
    whiteBotDepthSlider = new QSlider(Qt::Horizontal, this);
    whiteBotDepthSlider->setMinimum(1);
    whiteBotDepthSlider->setMaximum(8);
    whiteBotDepthSlider->setValue(5);
    whiteBotDepthSlider->setTickPosition(QSlider::TicksBelow);
    whiteBotDepthSlider->setTickInterval(1);
    whiteSliderLayout->addWidget(whiteBotDepthSlider);

    whiteBotDepthLabel = new QLabel("5", this);
    whiteBotDepthLabel->setMinimumWidth(30);
    whiteBotDepthLabel->setFont(buttonFont);
    whiteSliderLayout->addWidget(whiteBotDepthLabel);

    mainLayout->addLayout(whiteSliderLayout);

    mainLayout->addSpacing(10);

    QLabel* blackBotLabel = new QLabel("Black Bot Depth:", this);
    blackBotLabel->setFont(sectionFont);
    mainLayout->addWidget(blackBotLabel);

    QHBoxLayout* blackSliderLayout = new QHBoxLayout();
    blackBotDepthSlider = new QSlider(Qt::Horizontal, this);
    blackBotDepthSlider->setMinimum(1);
    blackBotDepthSlider->setMaximum(8);
    blackBotDepthSlider->setValue(5);
    blackBotDepthSlider->setTickPosition(QSlider::TicksBelow);
    blackBotDepthSlider->setTickInterval(1);
    blackSliderLayout->addWidget(blackBotDepthSlider);

    blackBotDepthLabel = new QLabel("5", this);
    blackBotDepthLabel->setMinimumWidth(30);
    blackBotDepthLabel->setFont(buttonFont);
    blackSliderLayout->addWidget(blackBotDepthLabel);

    mainLayout->addLayout(blackSliderLayout);

    mainLayout->addStretch();

    connect(playerVsBotButton, &QPushButton::clicked, this, &Menu::onPlayerVsBotClicked);
    connect(botVsBotButton, &QPushButton::clicked, this, &Menu::onBotVsBotClicked);
    connect(whiteBotDepthSlider, &QSlider::valueChanged, this, &Menu::onWhiteBotDepthChanged);
    connect(blackBotDepthSlider, &QSlider::valueChanged, this, &Menu::onBlackBotDepthChanged);
}

Menu::~Menu() {
}

void Menu::onPlayerVsBotClicked() {
    emit startGame(true, whiteBotDepth, blackBotDepth);
}

void Menu::onBotVsBotClicked() {
    emit startGame(false, whiteBotDepth, blackBotDepth);
}

void Menu::onWhiteBotDepthChanged(int value) {
    whiteBotDepth = value;
    whiteBotDepthLabel->setText(QString::number(value));
}

void Menu::onBlackBotDepthChanged(int value) {
    blackBotDepth = value;
    blackBotDepthLabel->setText(QString::number(value));
}
