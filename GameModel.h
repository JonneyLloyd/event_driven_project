#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "models/GenerateRoom.h"
#include "models/Player.h"
#include "models/Tile.h"
#include "models/InteractableTile.h"

#include "TileTypeEnum.h"
#include "DirectionEnum.h"

#include <QTimeLine>

/*
 * GameModel handles state and logic of the game.
 * Following MVC it is controlled externally.
 * State changes are transmitted to the controller via signals.
 *
 * Possibly create a game loop here using a timer asynchronously and emitting signals
 * if the state changes
 */
class GameModel : public QObject
{
    Q_OBJECT

public:
    explicit GameModel(QObject *parent = 0);

    GenerateRoom * getCurrentRoom();
    void setCurrentRoom(GenerateRoom * currentRoom);
    Player * getPlayer();
    void setPlayer(Player * player);

signals:
    void movePlayerEvent(Direction Direction);  // Notifies controller to move player
                                                // Should this be direction or position with animation=true default flag
    void displayFloorEvent(QHash<std::pair<int, int>, Tile *> * floor,
                           QHash<std::pair<int, int>, Tile *> * walls,
                           QHash<std::pair<int, int>, Tile *> * doors);

    void addInventoryItemEvent(int index, TileType type);
    void removeInventoryItemEvent(int index);

public slots:
    void move(Direction Direction);     // Listens for controller
                                        // Moves the player in game state
    void generateNewRoom();
    void generateNewRoom(int preset, int rows, int cols);
    void inventoryClick(int index);

private:
    bool playerMoving = false;
    Direction bufferedMove = Direction::UNKNOWN;
    QTimeLine * gameLoop;
    GenerateRoom * currentRoom;
    Player * player;
    void movePlayer(Direction Direction);

private slots:
    void nextGameLoop(int);

};

#endif // GAMEMODEL_H
