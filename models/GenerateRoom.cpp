#include "GenerateRoom.h"
#include "TileTypeEnum.h"
#include <QDebug>
#include <math.h>



GenerateRoom::GenerateRoom(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
}

GenerateRoom::~GenerateRoom()
{
    QHash<std::pair<int, int>, Tile*> ::iterator i;
    for (i = floor->begin(); i != floor->end(); ++i){
        floor->erase(i);
    }
    for (i = walls->begin(); i != walls->end(); ++i){
        walls->erase(i);
    }
    for (i = interactables->begin(); i != interactables->end(); ++i){
        interactables->erase(i);
    }
    QHash<std::pair<int, int>, InteractableTile*> :: iterator j;
    for (j = interactableDoors->begin(); j != interactableDoors->end(); ++j){
        interactableDoors->erase(j);
    }
}

void GenerateRoom::setRows(int rows)
{
    this->rows=rows;
}


void GenerateRoom::setColumns(int columns)
{
    this->columns=columns;
}


int GenerateRoom::getRows()  const
{
    return this->rows;
}


int GenerateRoom::getColumns()  const
{
    return this->columns;
}

//generate room using relative values so as to work with any dimensions
void GenerateRoom::generateRoom()
{
    walls = new QHash<std::pair<int, int>, Tile*> ;
    bool traversable = false;
    TileType::Enum id = TileType::WALL_W_U;
    Tile * westWall = new Tile(traversable, id);
    id = TileType::WALL_E_U;
    Tile * eastWall = new Tile(traversable, id);
    id = TileType::WALL_N_L;
    Tile * northWall = new Tile(traversable, id);
    id = TileType::WALL_S_U;
    Tile * southWall = new Tile(traversable, id);

    for(int i = 0; i < this->getRows(); i++){
        for(int j = 0; j < this->getColumns(); j++){
            if(i ==0 && j ==0)                          //northwest corner
            {
                id = TileType::WALL_NW_CORNER_L;
                walls->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i == this->getRows()-1 && j ==0)   //southwest corner
            {
                id = TileType::WALL_NE_CORNER_L;
                walls->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i == 0 && j ==this->getColumns()-1)         // north east corner
            {
                id = TileType::WALL_SW_CORNER_U;
                walls->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i == this->getRows()-1 && j == this->getColumns()-1) //south east corner
            {
                id = TileType::WALL_SE_CORNER_U;
                walls->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i ==0)
            {
                walls->insert(std::make_pair(i,j), westWall);
            }
            else if(i ==this->getRows()-1)
            {
                walls->insert(std::make_pair(i,j), eastWall);
            }
            else if(j ==0)
            {
                walls->insert(std::make_pair(i,j), northWall);
            }
            else if(j == getColumns()-1)
            {
                walls->insert(std::make_pair(i,j), southWall);
            }
        }
    }
}

void GenerateRoom::generateFloor()
{
    TileType::Enum id = TileType::FLOOR;
    bool traversable = true;
    Tile * floorTile = new Tile(traversable, id);
    floor = new QHash<std::pair<int, int>, Tile*> ;
    for(int i = 0; i < getRows(); i++){
        for(int j = 0; j < getColumns(); j++){
                floor->insert(std::make_pair(i,j), floorTile); //floor
        }
    }
}

void GenerateRoom::generateDoors()
{
    bool traversable = false;
    TileType::Enum id = TileType::DOOR;
    InteractableTile * doorTile = new InteractableTile("This is a door", traversable, id, true, TileType::ORB_BLUE);
    interactables = new QHash<std::pair<int, int>, Tile*> ;
    interactables->insert(std::make_pair(getRows()/2,0), doorTile); //north door
    id = TileType::DOOR_WEST;
    doorTile = new InteractableTile("This is a door", traversable, id);
    interactables->insert(std::make_pair(0,getColumns()/2), doorTile); //west door
    id = TileType::DOOR_EAST;
    doorTile = new InteractableTile("This is a door", traversable, id);
    interactables->insert(std::make_pair(getRows()-1,getColumns()/2), doorTile); //east door
    id = TileType::DOOR_SOUTH;
    doorTile = new InteractableTile("This is a door", traversable, id);
    interactables->insert(std::make_pair(getRows()/2,getColumns()-1), doorTile); //south door
}

void GenerateRoom::generateInteractableLayer(QHash<TileType::Enum, TileType::Enum> interactableList,
                                             QHash<TileType::Enum, bool> interactableState)
{
    interactables = new QHash<std::pair<int, int>, Tile*> ;
    bool traversable = false, state = false;
    int row = 0, col = 0;
    InteractableTile * doorTile;
    QString description;

    QHash<TileType::Enum, TileType::Enum>::iterator i;
    for (i = interactableList.begin(); i != interactableList.end(); ++i){
        row = 0;
        col = 0;
        state = interactableState.find(i.key()).value();
        if(i.value() == TileType::EMPTY)
            description = "An unlocked door...";
        else
            description = "This door has a strange key hole!";
        switch (i.key()){
            case TileType::DOOR :
                row = getRows()/2;
                col = 0;
                break;
            case TileType::GATE :
                row = getRows()/2;
                col = 0;
                description = "A heavy iron gate";
                break;
            case TileType::DOOR_WEST :
                row = 0;
                col = getColumns()/2;
                break;
            case TileType::DOOR_EAST :
                row = getRows()-1;
                col = getColumns()/2;
                break;
            case TileType::DOOR_SOUTH :
                row = getRows()/2;
                col = getColumns()-1;
                break;

             case TileType::CHEST :
                row = getRows()/2;
                col = getColumns()/2;
                description = "An unlocked chest...";
                break;
            case TileType::SWITCH :
               row = getRows()/3;
               col = getColumns()/3;
               description = "A switchable lever...";
               break;
            case TileType::Enum::NPC_GREEN :
               row = getRows()/2;
               col = getColumns()/2;
               description = "Want to be friends?\n\nFriends can touch your private parts...";
               break;
            case TileType::Enum::LAMP_BLUE :
                row = getRows()/2 + 1;
                col = 1;
                description = "What a nice light!";
                break;
            case TileType::Enum::LAMP_ORANGE :
                row = getRows()/2 - 1;
                col = 1;
                description = "Cool!";
                break;
            case TileType::Enum::LAMP_GREEN :
               row = getRows()/4;
               col = getColumns()/4;
               description = "What a nice light!";
               break;

            default: break;
        }
        doorTile = new InteractableTile(description, traversable, i.key(), state, i.value());
        interactables->insert(std::make_pair(row,col), doorTile);
    }
}

QHash<std::pair<int, int>, Tile *> * GenerateRoom::getFloor()  const
{
    return this->floor;
}

QHash<std::pair<int, int>, Tile *> * GenerateRoom::getWalls()  const
{
    return this->walls;
}

QHash<std::pair<int, int>, Tile *> *GenerateRoom::getInteractables()  const
{
    return this->interactables;
}

std::pair<int, int> GenerateRoom::getTileCoords(TileType::Enum tileName)  const

{
    QHash<std::pair<int, int>, Tile*>::iterator i;
    for (i = interactables->begin(); i != interactables->end(); ++i){
        if(i.value()->getId() == tileName)
            return i.key();
        }
    return std::make_pair(0,0);
}

