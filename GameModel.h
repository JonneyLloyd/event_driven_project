#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include "models/GenerateRoom.h"
#include "models/Player.h"
#include "models/Tile.h"
#include "models/InteractableTile.h"
#include "models/State.h"

#include "TileTypeEnum.h"
#include "DirectionEnum.h"

#include <QTimeLine>
#include <QHash>
#include <vector>

/*
 * GameModel handles state and logic of the game.
 * Following MVC it is controlled externally.
 * State changes are transmitted to the controller via signals.
 *
 * Possibly create a game loop here using a timer asynchronously and emitting signals
 * if the state changes
 */

//ref:
//http://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
template <typename T>
void remove(std::vector<T>& vec, unsigned int pos)
{
    typename std::vector<T>::iterator it = vec.begin();
    //You need typename to tell the compiler that ::iterator is supposed to be a type
    std::advance(it, pos);
    vec.erase(it);
}


class GameModel : public QObject
{
    Q_OBJECT

public:
    explicit GameModel(QObject *parent = 0);

    GenerateRoom * getCurrentRoom();
    void setCurrentRoom(GenerateRoom * currentRoom);
    Player * getPlayer()  const;
    void setPlayer(Player * player);
    void setRoomLocation(std::pair<int, int> roomLocation);
    std::pair<int, int> getRoomLocation()  const;
    void generateAllRoomStates();

signals:
    void movePlayerEvent(Direction::Enum direction);  // Notifies controller to move player
                                                // Should this be direction or position with animation=true default flag
    void displayFloorEvent(QHash<std::pair<int, int>, Tile *> * floor,
                           QHash<std::pair<int, int>, Tile *> * walls,
                           QHash<std::pair<int, int>, Tile *> * doors);
    void addInventoryItemEvent(int index, TileType::Enum type);
    void removeInventoryItemEvent(int index);
    void setPlayerLocationEvent(int x, int y);
    void setPlayerHeadingEvent(Direction::Enum);
    void displayMenuEvent(bool visible);
    void addMenuItemEvent(int index, QString text);

public slots:
    void move(Direction::Enum direction);     // Listens for controller
                                        // Moves the player in game state
    void generateNewRoom();
    void generateNewRoom(std::pair<int, int> roomLocation);
    void inventoryClick(int index);
    void interact();
    void menuClick(int index);
    void pauseClick();

private:
    bool playerMoving = false;
    Direction::Enum bufferedMove = Direction::UNKNOWN;
    QTimeLine * gameLoop;
    GenerateRoom * currentRoom;
    Player * player;
    std::pair<int, int> roomLocation;
    State * roomState;
    QHash<std::pair<int, int>,State*> * world;
    QHash<std::pair<int, int>, Tile*> * interactables;
    vector<TileType::Enum> inventory;
    void movePlayer(Direction::Enum direction);
    std::pair<int, int> winCondition;

private slots:
    void nextGameLoop(int);

};

#endif // GAMEMODEL_H
