#include "GameController.h"
#include <QDebug>

GameController::GameController(GameModel *gameModel, GameView *gameView, QObject *parent)
    : QObject(parent)
{
    gameModel = gameModel;
    gameView = gameView;
    connect(gameView, SIGNAL(moveEvent(Direction)), gameModel, SLOT(move(Direction)));
    connect(gameModel, SIGNAL(movePlayerEvent(Direction)), gameView, SLOT(movePlayer(Direction)));
    connect(gameModel, SIGNAL(displayFloorEvent(QHash<std::pair<int, int>, Tile *>*, QHash<std::pair<int, int>, Tile *>*)),
    gameView, SLOT(displayFloor(QHash<std::pair<int, int>, Tile *>*, QHash<std::pair<int, int>, Tile *>*)));

    gameModel->generateNewRoom();
}


