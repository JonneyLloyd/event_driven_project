#include "GenerateRoom.h"



GenerateRoom::GenerateRoom(int preset, int rows, int columns)
{
    if (preset <=0)
        preset = 1;
    this->preset = preset;
    this->rows = rows;
    this->columns = columns;
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


QHash<std::pair<int, int>, Tile*>  *GenerateRoom::generateRoom()
{
    QHash<std::pair<int, int>, Tile*> * result = new QHash<std::pair<int, int>, Tile*> ;
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
                result->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i == this->getRows()-1 && j ==0)   //southwest corner
            {
                id = 2;
                result->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i == 0 && j ==this->getColumns()-1)         // north east corner
            {
                id = 3;
                result->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i == this->getRows()-1 && j == this->getColumns()-1) //south east corner
            {
                id = 4;
                result->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            else if(i ==0)
            {
                result->insert(std::make_pair(i,j), westWall);
            }
            else if(i ==this->getRows()-1)
            {
                result->insert(std::make_pair(i,j), eastWall);
            }
            else if(j ==0)
            {
                result->insert(std::make_pair(i,j), northWall);
            }
            else if(j == getColumns()-1)
            {
                result->insert(std::make_pair(i,j), southWall);
            }

        }
    }
    return result;
}


QHash<std::pair<int, int>, Tile*> *GenerateRoom::generateItems()
{
    QHash<std::pair<int, int>, Tile*> * result = new QHash<std::pair<int, int>, Tile*> ;
    bool traversable = true;
    int id = 10;
    //inserting 4 doors, pos relative to preset
    result->insert(std::make_pair(0,getColumns()/this->getPreset()), new Tile(traversable, id));
    id = 11;
    result->insert(std::make_pair(0,getRows()/this->getPreset()), new Tile(traversable, id));
    id = 12;
    result->insert(std::make_pair(getColumns()/this->getPreset(),0), new Tile(traversable, id));
    id = 13;
    result->insert(std::make_pair(getRows()/this->getPreset(),0), new Tile(traversable, id));

    traversable = false;
    id = 14;
    //insert chest
    result->insert(std::make_pair(getRows()/this->getPreset()+1,getColumns()/this->getPreset()), new Tile(traversable, id));

    return result;
}


QHash<std::pair<int, int>, Tile*> *GenerateRoom::generateFloor()
{
    int id = 9;
    bool traversable = true;
    Tile * floor = new Tile(traversable, id);
    QHash<std::pair<int, int>, Tile*> * result = new QHash<std::pair<int, int>, Tile*> ;
    for(int i = 0; i < getRows(); i++){
        for(int j = 0; j < getColumns(); j++){
                result->insert(std::make_pair(i,j), floor); //floor
        }
    }


    return result;
}
