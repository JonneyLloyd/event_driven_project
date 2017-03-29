#include "GameModel.h"
#include "models/GenerateRoom.h"
#include "models/Player.h"
#include "models/Tile.h"

#include <QApplication>
#include <QDebug>


GameModel::GameModel(QObject *parent) : QObject(parent)
{
    world = new QHash<std::pair<int, int>,State*>;
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
    QHash<TileType::Enum, TileType::Enum> interactableContent;
    QHash<TileType::Enum, bool> interactableState;


    //Room 0,0
    interactableContent.insert(TileType::DOOR, TileType::ORB_GREEN);
    interactableContent.insert(TileType::DOOR_EAST, TileType::EMPTY);
    interactableContent.insert(TileType::CHEST, TileType::ORB_BLUE);
    interactableState.insert(TileType::DOOR, false);
    interactableState.insert(TileType::DOOR_EAST, false);
    interactableState.insert(TileType::CHEST, false);
    roomState = new State(std::make_pair(0,0), 16, 10, interactableContent, interactableState);
    world->insert(roomState->getRoomLocation(), roomState);
    interactableContent.clear();

    //Room 0,1
    interactableContent.insert(TileType::DOOR, TileType::EMPTY);
    interactableContent.insert(TileType::DOOR_WEST, TileType::EMPTY);
    interactableState.insert(TileType::DOOR, false);
    interactableState.insert(TileType::DOOR_WEST, false);
    roomState = new State(std::make_pair(0,1), 14, 10, interactableContent, interactableState);
    world->insert(roomState->getRoomLocation(), roomState);
    interactableContent.clear();

    //Room 1,0
    interactableContent.insert(TileType::DOOR, TileType::ORB_BLUE);
    interactableContent.insert(TileType::DOOR_SOUTH, TileType::EMPTY);
    interactableState.insert(TileType::DOOR, false);
    interactableState.insert(TileType::DOOR_SOUTH, false);
    roomState = new State(std::make_pair(1,0), 16, 10, interactableContent, interactableState);
    world->insert(roomState->getRoomLocation(), roomState);
    interactableContent.clear();

    //Room 1,1
    interactableContent.insert(TileType::DOOR_SOUTH, TileType::EMPTY);
    interactableContent.insert(TileType::CHEST, TileType::ORB_GREEN);
    interactableState.insert(TileType::DOOR_SOUTH, false);
    interactableState.insert(TileType::CHEST, false);
    roomState = new State(std::make_pair(1,1), 10, 6, interactableContent, interactableState);
    world->insert(roomState->getRoomLocation(), roomState);
    interactableContent.clear();

    //Room 2,0
    interactableContent.insert(TileType::DOOR, TileType::ORB_PINK);
    interactableContent.insert(TileType::DOOR_SOUTH, TileType::EMPTY);
    interactableContent.insert(TileType::DOOR_EAST, TileType::EMPTY);
    interactableState.insert(TileType::DOOR, false);
    interactableState.insert(TileType::DOOR_SOUTH, false);
    interactableState.insert(TileType::DOOR_EAST, false);
    roomState = new State(std::make_pair(2,0), 12, 8, interactableContent, interactableState);
    world->insert(roomState->getRoomLocation(), roomState);
    interactableContent.clear();

    //Room 2,1
    interactableContent.insert(TileType::DOOR_WEST, TileType::EMPTY);
    interactableContent.insert(TileType::CHEST, TileType::ORB_PINK);
    interactableState.insert(TileType::DOOR_WEST, false);
    interactableState.insert(TileType::CHEST, false);
    roomState = new State(std::make_pair(2,1), 8, 6, interactableContent, interactableState);
    world->insert(roomState->getRoomLocation(), roomState);
    interactableContent.clear();

    //Room 3,0
    //TODO OLIVER change door enum to gate
    interactableContent.insert(TileType::DOOR, TileType::SWITCH);
    interactableContent.insert(TileType::DOOR_SOUTH, TileType::EMPTY);
    //TODO OLIVER change door enum to gate
    interactableContent.insert(TileType::SWITCH, TileType::DOOR);
    //TODO OLIVER change door enum to gate
    interactableState.insert(TileType::DOOR, false);
    interactableState.insert(TileType::DOOR_SOUTH, false);
    interactableState.insert(TileType::SWITCH, false);
    roomState = new State(std::make_pair(3,0), 10, 6, interactableContent, interactableState);
    world->insert(roomState->getRoomLocation(), roomState);

    //Setting end of map
    winCondition = std::make_pair(4,0);
}

void GameModel::generateNewRoom()
{
    generateNewRoom(getRoomLocation());
}

void GameModel::generateNewRoom(std::pair<int, int> roomLocation)
{
    roomState = world->value(roomLocation);
    currentRoom = new GenerateRoom(roomState->getRows(),roomState->getCols());
    currentRoom->generateFloor();
    currentRoom->generateRoom();
    currentRoom->generateInteractableLayer(roomState->getInteractableContent(),
                                           roomState->getInteractableState());
    //Creating a player object with default position
    player = new Player(10,4);
    emit displayFloorEvent(currentRoom->getFloor(),
                           currentRoom->getWalls(), currentRoom->getInteractables());
    //Loop through inventory and send to view to display
    //inventory.size() returns unsigned int
    for(unsigned int i = 0; i < inventory.size(); i++)
        emit addInventoryItemEvent(i, inventory[i]);
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

Player * GameModel::getPlayer()  const
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
    QHash<std::pair<int, int>, Tile*> * doors = currentRoom->getInteractables();
    QHash<std::pair<int, int>, Tile*> * all = currentRoom->getFloor();
    //uniting all tiles into one QHash
    all->unite(*walls);
    all->unite(*doors);

    std::pair<int, int> coordinates;
    QHash<std::pair<int, int>, Tile*>::iterator i;

    //get x,y values for direction user is about to move
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
    interactables = currentRoom->getInteractables();
    std::pair<int, int> coordinates;
    Direction::Enum heading = player->getHeading();
    //get x,y values for direction user is about to interact with
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

        default:            qDebug() << "NO Interacable detected"; return;
    }

    if (interactables->contains(coordinates)){
    QHash<std::pair<int, int>, Tile*>::iterator i;
    //check if that coord actually contains an interactable
    i = interactables->find(coordinates);
    //check the interactable matches the inventory item
    if(((InteractableTile*)(i.value()))->getKey() == inventory[index]){
        //TODO OLIVER - change to dialog box
        qDebug() << ((InteractableTile*)(i.value()))->interact(inventory[index]);
        //update stored room state
        world->value(getRoomLocation())->changeInteractableContent(((InteractableTile*)(i.value()))->getId(),TileType::EMPTY);
        world->value(getRoomLocation())->changeInteractableContent(((InteractableTile*)(i.value()))->getId(),true);
        remove(inventory,index);
        emit removeInventoryItemEvent(index);
        }
    }
}


void GameModel::interact()
{
    interactables = currentRoom->getInteractables();
    std::pair<int, int> coordinates;
    QHash<std::pair<int, int>, Tile*>::iterator i;
    Direction::Enum heading = player->getHeading();
    //get x,y values for direction user is about to interact with
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

    int x = getRoomLocation().first;
    int y = getRoomLocation().second;
    Direction::Enum direction = Direction::UNKNOWN;
    if (interactables->contains(coordinates)){
        i = interactables->find(coordinates);
        //TODO OLIVER - change to dialog box
        qDebug() << ((InteractableTile*)(i.value()))->interact();
        //Check what player is interacting with and handle
        if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR_EAST &&
                ((InteractableTile*)(i.value()))->getState() == true)
        {
            setRoomLocation(std::make_pair(x,y+1));
            generateNewRoom();
            player->setXY(1,getCurrentRoom()->getColumns()/2);
            direction = (Direction::EAST);
            emit setPlayerLocationEvent(1,getCurrentRoom()->getColumns()/2);
            //signal for animation
        }
        else if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR_WEST &&
                 ((InteractableTile*)(i.value()))->getState() == true){
            setRoomLocation(std::make_pair(x,y-1));
            generateNewRoom();
            player->setXY(getCurrentRoom()->getRows()-2,getCurrentRoom()->getColumns()/2);
            direction = (Direction::WEST);
            emit setPlayerLocationEvent(getCurrentRoom()->getRows()-2,getCurrentRoom()->getColumns()/2);
            //signal for animation
        }
        else if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR &&
                 ((InteractableTile*)(i.value()))->getState() == true){
            setRoomLocation(std::make_pair(x+1,y));
            generateNewRoom();
            player->setXY(getCurrentRoom()->getRows() /2,getCurrentRoom()->getColumns()-2);
            direction = (Direction::NORTH);
            emit setPlayerLocationEvent(getCurrentRoom()->getRows() /2,getCurrentRoom()->getColumns()-2);
            //signal for animation
        }
        else if (((InteractableTile*)(i.value()))->getId() == TileType::DOOR_SOUTH &&
                 ((InteractableTile*)(i.value()))->getState() == true){
            setRoomLocation(std::make_pair(x-1,y));
            generateNewRoom();
            player->setXY(getCurrentRoom()->getRows() /2,1);
            direction = (Direction::SOUTH);
            emit setPlayerLocationEvent(getCurrentRoom()->getRows() /2,1);
            //signal for animation
        }
        else if (((InteractableTile*)(i.value()))->getId() == TileType::CHEST &&
                 ((InteractableTile*)(i.value()))->getKey() != TileType::EMPTY){
            inventory.push_back(((InteractableTile*)(i.value()))->getKey());
            emit addInventoryItemEvent(inventory.size(), ((InteractableTile*)(i.value()))->getKey());
            ((InteractableTile*)(i.value()))->setKey(TileType::EMPTY);
            world->value(getRoomLocation())->changeInteractableContent(((InteractableTile*)(i.value()))->getId(),TileType::EMPTY);
            world->value(getRoomLocation())->changeInteractableContent(((InteractableTile*)(i.value()))->getId(),true);
            qDebug() << "You found an odd shaped key in the chest...";
        }

        else if (((InteractableTile*)(i.value()))->getId() == TileType::SWITCH){
            //TODO OLIVER use dialor box here
            qDebug() << "You switched the lever...";
            //std::pair<int, int> doorCoords = interactables->key(((InteractableTile*)(i.value()))->getKey());
            std::pair<int, int> doorCoords = currentRoom->getTileCoords(((InteractableTile*)(i.value()))->getKey());
            QHash<std::pair<int, int>, Tile*>::iterator temp;
            temp = interactables->find(doorCoords);
            //TODO OLIVER use dialor box here
            qDebug() << ((InteractableTile*)(temp.value()))->interact(TileType::SWITCH);

            //TODO OLIVER animations for gate and switch
            //no need to save state as this will be win condition
        }
        //Set direction player is facing on the view
        if (direction != Direction::UNKNOWN){
            emit setPlayerHeadingEvent(direction);
        }
    }
}


void GameModel::setRoomLocation(std::pair<int, int> roomLocation)
{
    if (roomLocation == winCondition){
        //TODO OLIVER pop up win screen here

    }
    else
        this->roomLocation = roomLocation;
}

std::pair<int, int> GameModel::getRoomLocation()  const
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

