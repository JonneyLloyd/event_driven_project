#include "GameModel.h"
#include "models/GenerateRoom.h"
#include "models/Player.h"
#include "models/Tile.h"

#include <QDebug>

GameModel::GameModel(QObject *parent) : QObject(parent)
{

    setRoomLocation(std::make_pair(0,0));
    gameLoop = new QTimeLine(600);
    gameLoop->setCurveShape(QTimeLine::LinearCurve);
    gameLoop->setFrameRange(0, 5);
    connect(gameLoop, SIGNAL(frameChanged(int)), SLOT(nextGameLoop(int)));
    gameLoop->start();
    gameLoop->setLoopCount(0);  // forever
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
    InteractableTile * test = new InteractableTile("Testing", true, TileType::DOOR);
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
    // Buffers movement input to allow current move to finish
    // Input will be deffered and dispatched at each game loop
    bufferedMove = direction;
}

void GameModel::movePlayer(Direction direction)
{
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
            player->setHeading(Direction::WEST);
        }
        break;

        case Direction::EAST:
        coordinates = std::make_pair (player->getX()+1, player->getY());
        i = all->find(coordinates);
        qDebug() << "key "<< i.key() << "Traversable " << i.value()->getTraversable();
        if (i.value()->getTraversable() == true){
            emit movePlayerEvent(direction);
            player->setXY(player->getX()+1, player->getY());
            player->setHeading(Direction::EAST);
        }
        break;

        case Direction::NORTH:
        coordinates = std::make_pair (player->getX(), player->getY()-1);
        i = all->find(coordinates);
        qDebug() << "key "<< i.key() << "Traversable " << i.value()->getTraversable();
        if (i.value()->getTraversable() == true){
            emit movePlayerEvent(direction);
            player->setXY(player->getX(), player->getY()-1);
            player->setHeading(Direction::NORTH);
        }
        break;

        case Direction::SOUTH:
        coordinates = std::make_pair (player->getX(), player->getY()+1);
        i = all->find(coordinates);
        qDebug() << "key "<< i.key() << "Traversable " << i.value()->getTraversable();
        if (i.value()->getTraversable() == true){
            emit movePlayerEvent(direction);
            player->setXY(player->getX(), player->getY()+1);
            player->setHeading(Direction::SOUTH);
        }
        break;

        default:            qDebug() << "NO MOVEMENT"; return;
    }

    //query player pos and qHash to check if move is valid
    i = all->find(coordinates);
    qDebug() << "key "<< i.key() << "Traversable " << i.value()->getTraversable();
    if (i.value()->getTraversable() == true){
        emit movePlayerEvent(direction);
        player->setXY(coordinates.first, coordinates.second);
    }
}

void GameModel::inventoryClick(int index)
{
    // TODO: some logic
    emit removeInventoryItemEvent(index);
}


void GameModel::interact()
{
    QHash<std::pair<int, int>, Tile*> * doors = currentRoom->getDoors();
    std::pair<int, int> coordinates;
    QHash<std::pair<int, int>, Tile*>::iterator i;
    Direction heading = player->getHeading();

    switch (heading){
        case Direction::WEST:
        coordinates = std::make_pair (player->getX()-1, player->getY());
        break;

        case Direction::EAST:
        coordinates = std::make_pair (player->getX()+1, player->getY());
        break;

        case Direction::NORTH:
        coordinates = std::make_pair (player->getX(), player->getY()-1);
        break;

        case Direction::SOUTH:
        coordinates = std::make_pair (player->getX(), player->getY()+1);
        break;

        default:            qDebug() << "NO MOVEMENT"; return;
    }
    /*
     * TODO
     * Working but will have to look at tidier way to traverse rooms
     * */
    if (doors->contains(coordinates)){
        i = doors->find(coordinates);
        qDebug() << ((InteractableTile*)(i.value()))->interact();
        if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR_EAST
                && getRoomLocation() == std::make_pair(0,0))
        {
            moveRoom();
            setRoomLocation(std::make_pair(0,1));
            player->setXY(1,getCurrentRoom()->getColumns()/2);
            emit setPlayerLocation(1,getCurrentRoom()->getColumns()/2);
        }
        if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR_WEST
                && getRoomLocation() == std::make_pair(0,1))
        {
            moveRoom();
            setRoomLocation(std::make_pair(0,0));

            player->setXY(getCurrentRoom()->getRows()-2,getCurrentRoom()->getColumns()/2);
            emit setPlayerLocation(getCurrentRoom()->getRows()-2,getCurrentRoom()->getColumns()/2);
        }
    }
}

void GameModel::moveRoom()
{
    //TODO hardcoded for now
    qDebug() << "moving Room";
    generateNewRoom(2,24,14);



}

void GameModel::setRoomLocation(std::pair<int, int> roomLocation)
{
    this->roomLocation = roomLocation;
}

std::pair<int, int> GameModel::getRoomLocation()
{
    return this->roomLocation;
}

void GameModel::nextGameLoop(int frame)
{
    if (frame == 0 && bufferedMove != Direction::UNKNOWN) {
        // Allow the player to move at the start of each game loop / clock cycle
        playerMoving = true;    // Movement in progress
        movePlayer(bufferedMove);
    }
    if (frame < 3 && playerMoving) {
        // ignore all movement input for the first half of the loop
        // if there is a movement in progress
        // otherwise, if the user is stationary, accept input at any time
        bufferedMove = Direction::UNKNOWN;
    }
    else if (frame == 4) {
        playerMoving = false;
    }
}

