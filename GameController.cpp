#include "GameController.h"
#include <QDebug>

GameController::GameController(GameModel *gameModel, GameView *gameView, QObject *parent)
    : QObject(parent)
{
    gameModel = gameModel;
    gameView = gameView;
    connect(gameView, SIGNAL(moveEvent(Direction::Enum)), gameModel, SLOT(move(Direction::Enum)));
    connect(gameModel, SIGNAL(movePlayerEvent(Direction::Enum)), gameView, SLOT(movePlayer(Direction::Enum)));

    connect(gameModel, SIGNAL(displayFloorEvent(QHash<std::pair<int, int>, Tile *>*,
                                                QHash<std::pair<int, int>, Tile *>*,
                                                QHash<std::pair<int, int>, Tile *>*)),
            gameView, SLOT(displayFloor(QHash<std::pair<int, int>, Tile *>*,
                                        QHash<std::pair<int, int>, Tile *>*,
                                        QHash<std::pair<int, int>, Tile *>*)));

    connect(gameView, SIGNAL(inventoryClickEvent(int)), gameModel, SLOT(inventoryClick(int)));
    connect(gameModel, SIGNAL(addInventoryItemEvent(int,TileType::Enum)), gameView, SLOT(addInventoryItem(int,TileType::Enum)));
    connect(gameModel, SIGNAL(removeInventoryItemEvent(int)), gameView, SLOT(removeInventoryItem(int)));
    
    connect(gameView, SIGNAL(interactEvent()), gameModel, SLOT(interact()));
    connect(gameModel, SIGNAL(setPlayerLocationEvent(int, int)), gameView, SLOT(setPlayerLocation(int, int)));
    connect(gameModel, SIGNAL(setPlayerHeadingEvent(Direction::Enum)), gameView, SLOT(setPlayerHeading(Direction::Enum)));

    connect(gameView, SIGNAL(pauseClickEvent()), gameModel, SLOT(pauseClick()));
    connect(gameView, SIGNAL(menuClickEvent(int)), gameModel, SLOT(menuClick(int)));
    connect(gameModel, SIGNAL(displayMenuEvent(bool)), gameView, SLOT(displayMenu(bool)));
    connect(gameModel, SIGNAL(addMenuItemEvent(int, QString)), gameView, SLOT(addMenuItem(int, QString)));

    connect(this, SIGNAL(generateNewRoom()), gameModel, SLOT(generateNewRoom()));
    emit generateNewRoom();
}

// TODO: maybe a start method to emit the first signal?
