#include "GameModel.h"
#include "models/GenerateRoom.h"
#include "models/Player.h"
#include "models/Tile.h"


#include <QApplication>
#include <QDebug>

GameModel::GameModel(QObject *parent) : QObject(parent)
{

    setRoomLocation(std::make_pair(0,0));
    generateAllRoomStates();
    gameLoop = new QTimeLine(600);
    gameLoop->setCurveShape(QTimeLine::LinearCurve);
    gameLoop->setFrameRange(0, 5);
    connect(gameLoop, SIGNAL(frameChanged(int)), SLOT(nextGameLoop(int)));
    gameLoop->start();
    gameLoop->setLoopCount(0);  // forever
}

void GameModel::generateAllRoomStates(){
    QHash<TileType::Enum, TileType::Enum> interactables;
    interactables.insert(TileType::Enum::DOOR, TileType::Enum::EMPTY);
    interactables.insert(TileType::Enum::DOOR_EAST, TileType::Enum::EMPTY);
    roomState = new State(std::make_pair(0,0), 20, 12, interactables);
    world.insert(roomState->getRoomLocation(), roomState);

    interactables.clear();
    interactables.insert(TileType::Enum::DOOR, TileType::Enum::EMPTY);
    interactables.insert(TileType::Enum::DOOR_WEST, TileType::Enum::EMPTY);
    roomState = new State(std::make_pair(0,1), 20, 12, interactables);
    world.insert(roomState->getRoomLocation(), roomState);

    interactables.clear();
    interactables.insert(TileType::Enum::DOOR_SOUTH, TileType::Enum::EMPTY);
    interactables.insert(TileType::Enum::DOOR_WEST, TileType::Enum::EMPTY);
    roomState = new State(std::make_pair(1,1), 20, 12, interactables);
    world.insert(roomState->getRoomLocation(), roomState);

    interactables.clear();
    interactables.insert(TileType::Enum::DOOR_SOUTH, TileType::Enum::EMPTY);
    interactables.insert(TileType::Enum::DOOR_EAST, TileType::Enum::EMPTY);
    roomState = new State(std::make_pair(1,0), 20, 12, interactables);
    world.insert(roomState->getRoomLocation(), roomState);
}


void GameModel::generateNewRoom()
{
    generateNewRoom(getRoomLocation());
}

void GameModel::generateNewRoom(std::pair<int, int> roomLocation)
{
    roomState = world.value(roomLocation);
    currentRoom = new GenerateRoom(1, roomState->getRows(),roomState->getCols());
    currentRoom->generateFloor();
    currentRoom->generateRoom();
    currentRoom->generateDoors(roomState->getInteractables());
    player = new Player(10,4);
    emit displayFloorEvent(currentRoom->getFloor(), currentRoom->getWalls(), currentRoom->getDoors());

    emit addInventoryItemEvent(0, TileType::ORB_BLUE);
    emit addInventoryItemEvent(1, TileType::ORB_ORANGE);
    emit addInventoryItemEvent(2, TileType::ORB_GREEN);
    emit addInventoryItemEvent(3, TileType::CHEST);
    emit addInventoryItemEvent(4, TileType::CHEST);

    // TODO: enum or vector
    emit addMenuItemEvent(0, QString("Resume"));
    emit addMenuItemEvent(1, QString("Options"));
    emit addMenuItemEvent(2, QString("Quit"));
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


void GameModel::move(Direction::Enum direction)
{
    // Buffers movement input to allow current move to finish
    // Input will be deffered and dispatched at each game loop
    bufferedMove = direction;
}

void GameModel::movePlayer(Direction::Enum direction)
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

    //query player pos and qHash to check if move is valid
    i = all->find(coordinates);
    qDebug() << "key "<< i.key() << "Traversable " << i.value()->getTraversable();
    if (i.value()->getTraversable() == true){
        emit movePlayerEvent(direction);
        player->setXY(coordinates.first, coordinates.second);
        player->setHeading(direction);
    }
    else {
        emit setPlayerHeadingEvent(direction);
    }
    player->setHeading(direction);
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
    Direction::Enum heading = player->getHeading();

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
    int x = getRoomLocation().first;
    int y = getRoomLocation().second;
    if (doors->contains(coordinates)){
        i = doors->find(coordinates);
        qDebug() << ((InteractableTile*)(i.value()))->interact();
        if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR_EAST)
        {
            setRoomLocation(std::make_pair(x,y+1));

        }
        else if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR_WEST){

            setRoomLocation(std::make_pair(x,y-1));

        }
        else if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR){

            setRoomLocation(std::make_pair(x+1,y));

        }
        else if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR_SOUTH){

            setRoomLocation(std::make_pair(x-1,y));

        }

        generateNewRoom();
        player->setXY(getCurrentRoom()->getRows()-2,getCurrentRoom()->getColumns()/2);
        emit setPlayerLocationEvent(getCurrentRoom()->getRows()-2,getCurrentRoom()->getColumns()/2);
    }
}


void GameModel::setRoomLocation(std::pair<int, int> roomLocation)
{
    this->roomLocation = roomLocation;
}

std::pair<int, int> GameModel::getRoomLocation()
{
    return this->roomLocation;
}

void GameModel::menuClick(int index)
{
    // TODO: some logic
    if (index==2)
        QApplication::quit();
    emit displayMenuEvent(false);

}

void GameModel::pauseClick()
{
    // TODO: some logic
    emit displayMenuEvent(true);
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

