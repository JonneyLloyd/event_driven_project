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
    interactableContent.insert(TileType::DOOR, TileType::Enum::ORB_GREEN);
    interactableContent.insert(TileType::DOOR_EAST, TileType::Enum::EMPTY);
    interactableContent.insert(TileType::CHEST, TileType::Enum::ORB_BLUE);
    interactableContent.insert(TileType::LAMP_ORANGE, TileType::Enum::EMPTY);
    interactableContent.insert(TileType::LAMP_BLUE, TileType::Enum::EMPTY);
    interactableState.insert(TileType::DOOR, false);
    interactableState.insert(TileType::DOOR_EAST, false);
    interactableState.insert(TileType::CHEST, false);
    interactableState.insert(TileType::LAMP_ORANGE, false);
    interactableState.insert(TileType::LAMP_BLUE, false);
    roomState = new State(std::make_pair(0,0), 16, 10, interactableContent, interactableState);
    world->insert(roomState->getRoomLocation(), roomState);
    interactableContent.clear();

    //Room 0,1
    interactableContent.insert(TileType::DOOR, TileType::Enum::EMPTY);
    interactableContent.insert(TileType::DOOR_WEST, TileType::Enum::EMPTY);
    interactableContent.insert(TileType::NPC_GREEN, TileType::Enum::EMPTY);
    interactableState.insert(TileType::DOOR, false);
    interactableState.insert(TileType::DOOR_WEST, false);
    interactableState.insert(TileType::NPC_GREEN, false);
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
    roomState = new State(std::make_pair(1,1), 10, 8, interactableContent, interactableState);
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
    interactableContent.insert(TileType::GATE, TileType::SWITCH);
    interactableContent.insert(TileType::DOOR_SOUTH, TileType::EMPTY);
    interactableContent.insert(TileType::SWITCH, TileType::GATE);
    interactableState.insert(TileType::GATE, false);
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

    interactables = currentRoom->getInteractables();
    QHash<std::pair<int, int>, Tile*>::iterator i;
    for (i = interactables->begin(); i != interactables->end(); ++i) {
        InteractableTile * tile = (InteractableTile*) i.value();
        bool state = tile->getState();
        if (state)  // TODO check
            emit setInteractableItemState(i.key(), true, 1);
    }

    // TODO tidy
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

        default: return;
    }

    //query player pos and qHash to check if move is valid
    i = all->find(coordinates);
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
        QHash<std::pair<int, int>, Tile*>::iterator t;
        t = interactables->find(coordinates);
        InteractableTile * i = (InteractableTile*) t.value();
        if(i->getKey() == inventory[index]){
            QString msg = i->interact(inventory[index]);
            emit displayDialogEvent(msg);
            world->value(getRoomLocation())->changeInteractableContent(i->getId(),TileType::EMPTY);
            world->value(getRoomLocation())->changeInteractableContent(i->getId(),true);
            emit setInteractableItemState(coordinates, i->getState(), 1);
            remove(inventory,index);
            emit removeInventoryItemEvent(index);
        }
    }
}


void GameModel::interact()
{
    interactables = currentRoom->getInteractables();
    std::pair<int, int> coordinates;
    QHash<std::pair<int, int>, Tile*>::iterator t;
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
        t = interactables->find(coordinates);
        InteractableTile * i = (InteractableTile*) t.value();
        if (i->getId() == TileType::DOOR_EAST &&
                i->getState() == true)
        {
            setRoomLocation(std::make_pair(x,y+1));
            generateNewRoom();
            player->setXY(1,getCurrentRoom()->getColumns()/2);
            direction = (Direction::EAST);
            emit setPlayerLocationEvent(1,getCurrentRoom()->getColumns()/2);
            //signal for animation
        }
        else if (i->getId() == TileType::DOOR_WEST &&
                 i->getState() == true){
            setRoomLocation(std::make_pair(x,y-1));
            generateNewRoom();
            player->setXY(getCurrentRoom()->getRows()-2,getCurrentRoom()->getColumns()/2);
            direction = (Direction::WEST);
            emit setPlayerLocationEvent(getCurrentRoom()->getRows()-2,getCurrentRoom()->getColumns()/2);
            //signal for animation
        }
        else if (i->getId() == TileType::DOOR &&
                 i->getState() == true){
            setRoomLocation(std::make_pair(x+1,y));
            generateNewRoom();
            player->setXY(getCurrentRoom()->getRows() /2,getCurrentRoom()->getColumns()-2);
            direction = (Direction::NORTH);
            emit setPlayerLocationEvent(getCurrentRoom()->getRows() /2,getCurrentRoom()->getColumns()-2);
            //signal for animation
        }
        else if (i->getId() == TileType::GATE &&
                 i->getState() == true){
            setRoomLocation(std::make_pair(x+1,y));
            //signal for animation
        }
        else if (i->getId() == TileType::DOOR_SOUTH &&
                 i->getState() == true){
            setRoomLocation(std::make_pair(x-1,y));
            generateNewRoom();
            player->setXY(getCurrentRoom()->getRows() /2,1);
            direction = (Direction::SOUTH);
            emit setPlayerLocationEvent(getCurrentRoom()->getRows() /2,1);
            //signal for animation
        }
        else {
            QString msg = i->getDescription();
            if (i->getId() == TileType::CHEST &&
                     i->getKey() != TileType::EMPTY){
                inventory.push_back(i->getKey());
                emit addInventoryItemEvent(inventory.size(), i->getKey());
                i->setKey(TileType::EMPTY);
                world->value(getRoomLocation())->changeInteractableContent(i->getId(),TileType::EMPTY);
                world->value(getRoomLocation())->changeInteractableContent(i->getId(),true);
                msg = QString("You found an odd shaped key in the chest...");  // TODO toggle msg when state changes (in interactable code?)
                emit setInteractableItemState(coordinates, true, 1);
            }
            else if (i->getId() == TileType::SWITCH){
                msg = QString("You switched the lever...");
                std::pair<int, int> doorCoords = currentRoom->getTileCoords(i->getKey());
                QHash<std::pair<int, int>, Tile*>::iterator temp;
                temp = interactables->find(doorCoords);
                InteractableTile * t = (InteractableTile*)(temp.value());
                t->setState(!(t->getState()));
                i->setState(!(i->getState()));

                emit setInteractableItemState(coordinates, i->getState(), 1);  // switch
                emit setInteractableItemState(doorCoords, t->getState(), 1);
            }
            else {
                msg = i->interact();
                if (i->getId() == TileType::DOOR) {
                    if (i->getState())
                        emit setInteractableItemState(coordinates, i->getState(), 1);
                    world->value(getRoomLocation())->changeInteractableContent(i->getId(),TileType::DOOR);
                    world->value(getRoomLocation())->changeInteractableContent(i->getId(),true);
                }
            }

            emit displayDialogEvent(msg);
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
        emit displayGameOverMenuEvent();
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

void GameModel::gameOverMenuClick()
{
    QApplication::quit();
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

