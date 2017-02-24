#include "GameController.h"

GameController::GameController(QMainWindow &mainWindow, QObject *parent)
    : QObject(parent)
{
    mainWindow.setCentralWidget(&gameView);

//    mainWindow.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
//    mainWindow.showFullScreen();
//    mainWindow.showMaximized();

    connect(&gameView, SIGNAL(moveEvent(Direction)), &gameModel, SLOT(move(Direction)));
    connect(&gameModel, SIGNAL(movePlayerEvent(Direction)), &gameView, SLOT(movePlayer(Direction)));
}
