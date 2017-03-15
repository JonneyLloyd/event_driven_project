#include "GenerateRoom.h"



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
    int id = 5;
    Tile * westWall = new Tile(traversable, id);
    id = 6;
    Tile * eastWall = new Tile(traversable, id);
    id = 7;
    Tile * northWall = new Tile(traversable, id);
    id = 8;
    Tile * southWall = new Tile(traversable, id);

    for(int i = 0; i < this->getRows(); i++){
        for(int j = 0; j < this->getColumns(); j++){
            if(i ==0 && j ==0)                          //northwest corner
            {
                id = 1;
                walls->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i == this->getRows()-1 && j ==0)   //southwest corner
            {
                id = 2;
                walls->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i == 0 && j ==this->getColumns()-1)         // north east corner
            {
                id = 3;
                walls->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i == this->getRows()-1 && j == this->getColumns()-1) //south east corner
            {
                id = 4;
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
    int id = 9;
    bool traversable = true;
    Tile * floorTile = new Tile(traversable, id);
    floor = new QHash<std::pair<int, int>, Tile*> ;
    for(int i = 0; i < getRows(); i++){
        for(int j = 0; j < getColumns(); j++){
                floor->insert(std::make_pair(i,j), floorTile); //floor
        }
    }
}

QHash<std::pair<int, int>, Tile *> * GenerateRoom::getFloor()
{
    return this->floor;
}

QHash<std::pair<int, int>, Tile *> * GenerateRoom::getWalls()
{
    return this->walls;
}
