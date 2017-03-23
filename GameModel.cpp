#include "GameModel.h"
#include "models/GenerateRoom.h"
#include "models/Player.h"
#include "models/Tile.h"

#include <QDebug>

GameModel::GameModel(QObject *parent) : QObject(parent)
{

}

void GameModel::generateNewRoom()
{
    generateNewRoom(2,20,12);
}

void GameModel::generateNewRoom(int preset, int rows, int cols)
{
    currentRoom = new GenerateRoom(preset,rows,cols);//TODO hardcoded for now
    currentRoom->generateFloor();
    currentRoom->generateRoom();
    currentRoom->generateDoors();
    player = new Player(10,4); //TODO hardcoded for now & independent of view
    emit displayFloorEvent(currentRoom->getFloor(), currentRoom->getWalls(), currentRoom->getDoors());
    qDebug() << "Floor mapping emmitted. floor size: " << currentRoom->getFloor()->size();


    /*
     * Testing InteractableTile
    InteractableTile * test = new InteractableTile("Testing", TileType::DOOR, true, 666);
    qDebug() << "Testing InteractibleFile " << test->getDescription();
    */

    // TODO: move
    addInventoryItemEvent(0, TileType::ORB_BLUE);
    addInventoryItemEvent(1, TileType::ORB_ORANGE);
    addInventoryItemEvent(2, TileType::ORB_GREEN);
    addInventoryItemEvent(3, TileType::CHEST);
    addInventoryItemEvent(4, TileType::CHEST);

}

GenerateRoom *GameModel::getCurrentRoom()
{
    return this->currentRoom;
}

void GameModel::setCurrentRoom(GenerateRoom *currentRoom)
{
    this->currentRoom = currentRoom;
}

Player * GameModel::getPlayer()
{
    return this->player;
}

void GameModel::setPlayer(Player * player)
{
    this->player = player;
}

void GameModel::move(Direction direction)
{
    qDebug() << "GameModel: Valid move";

    QHash<std::pair<int, int>, Tile*> * walls = currentRoom->getWalls();
    QHash<std::pair<int, int>, Tile*> * doors = currentRoom->getDoors();
    QHash<std::pair<int, int>, Tile*> * all = currentRoom->getFloor();
    all->unite(*walls);
    all->unite(*doors);

    std::pair<int, int> coordinates;
    QHash<std::pair<int, int>, Tile*>::iterator i;

    switch (direction){
        case Direction::WEST:
        coordinates = std::make_pair (player->getX()-1, player->getY());
        i = all->find(coordinates);
        qDebug() << "key "<< i.key() << "Traversable " << i.value()->getTraversable();
        if (i.value()->getTraversable() == true){
            emit movePlayerEvent(direction);
            player->setXY(player->getX()-1, player->getY());
        }
        break;

        case Direction::EAST:
        coordinates = std::make_pair (player->getX()+1, player->getY());
        i = all->find(coordinates);
        qDebug() << "key "<< i.key() << "Traversable " << i.value()->getTraversable();
        if (i.value()->getTraversable() == true){
            emit movePlayerEvent(direction);
            player->setXY(player->getX()+1, player->getY());
        }
        break;

        case Direction::NORTH:
        coordinates = std::make_pair (player->getX(), player->getY()-1);
        i = all->find(coordinates);
        qDebug() << "key "<< i.key() << "Traversable " << i.value()->getTraversable();
        if (i.value()->getTraversable() == true){
            emit movePlayerEvent(direction);
            player->setXY(player->getX(), player->getY()-1);
        }
        break;

        case Direction::SOUTH:
        coordinates = std::make_pair (player->getX(), player->getY()+1);
        i = all->find(coordinates);
        qDebug() << "key "<< i.key() << "Traversable " << i.value()->getTraversable();
        if (i.value()->getTraversable() == true){
            emit movePlayerEvent(direction);
            player->setXY(player->getX(), player->getY()+1);
        }
        break;

        default:            qDebug() << "NO MOVEMENT"; return;
    }

    //query player pos and qHash to check if move is valid
    //emit movePlayerEvent(direction);
}

void GameModel::inventoryClick(int index)
{
    // TODO: some logic
    emit removeInventoryItemEvent(index);
}

