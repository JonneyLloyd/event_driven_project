#include "GameController.h"

GameController::GameController(GameModel *gameModel, GameView *gameView, QObject *parent)
    : QObject(parent)
{
    gameModel = gameModel;
    gameView = gameView;
    connect(gameView, SIGNAL(moveEvent(Direction)), gameModel, SLOT(move(Direction)));
    connect(gameModel, SIGNAL(movePlayerEvent(Direction)), gameView, SLOT(movePlayer(Direction)));
}
