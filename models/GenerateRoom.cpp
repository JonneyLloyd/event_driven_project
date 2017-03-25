#include "GenerateRoom.h"
#include "TileTypeEnum.h"
#include <QDebug>



GenerateRoom::GenerateRoom(int preset, int rows, int columns)
{
    if (preset <=0)
        preset = 1;
    this->preset = preset;
    this->rows = rows;
    this->columns = columns;
}

GenerateRoom::~GenerateRoom()
{

}


void GenerateRoom::setPreset(int preset)
{
    this->preset=preset;
}


void GenerateRoom::setRows(int rows)
{
    this->rows=rows;
}


void GenerateRoom::setColumns(int columns)
{
    this->columns=columns;
}


int GenerateRoom::getPreset()
{
    return this->preset;
}


int GenerateRoom::getRows()
{
    return this->rows;
}


int GenerateRoom::getColumns()
{
    return this->columns;
}


void GenerateRoom::generateRoom()
{
    walls = new QHash<std::pair<int, int>, Tile*> ;
    bool traversable = false;
    TileType id = TileType::WALL_W_U;
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
    TileType id = TileType::FLOOR;
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
    TileType id = TileType::DOOR;
    InteractableTile * doorTile = new InteractableTile("This is a door", traversable, id, true, TileType::ORB_BLUE);
    doors = new QHash<std::pair<int, int>, Tile*> ;
    doors->insert(std::make_pair(getRows()/2,0), doorTile); //north door


    id = TileType::DOOR_SIDE;
    doorTile = new InteractableTile("This is a door", traversable, id);
    doors->insert(std::make_pair(0,getColumns()/2), doorTile); //west door
    doors->insert(std::make_pair(getRows()-1,getColumns()/2), doorTile); //east door
    doors->insert(std::make_pair(getRows()/2,getColumns()-1), doorTile); //south door
}

QHash<std::pair<int, int>, Tile *> * GenerateRoom::getFloor()
{
    return this->floor;
}

QHash<std::pair<int, int>, Tile *> * GenerateRoom::getWalls()
{
    return this->walls;
}

QHash<std::pair<int, int>, Tile *> *GenerateRoom::getDoors()
{
    return this->doors;
}
