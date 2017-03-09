#include "GenerateRoom.h"



GenerateRoom::GenerateRoom(int preset, int length, int width)
{
    if (preset <=0)
        preset = 1;
    this->preset = preset;
    this->length = length;
    this->width = width;
}


void GenerateRoom::setPreset(int preset)
{
    this->preset=preset;
}


void GenerateRoom::setLength(int length)
{
    this->length=length;
}


void GenerateRoom::setWidth(int width)
{
    this->width=width;
}


int GenerateRoom::getPreset()
{
    return this->preset;
}


int GenerateRoom::getLength()
{
    return this->length;
}


int GenerateRoom::getWidth()
{
    return this->width;
}


QHash<std::pair<int, int>, Tile*>  *GenerateRoom::generateRoom()
{
    QHash<std::pair<int, int>, Tile*> * result = new QHash<std::pair<int, int>, Tile*> ;
    bool traversable = true;
    int id = 0;
    for(int i = 0; i < getLength(); i++){
        for(int j = 0; j < getWidth(); j++){
            if(i == 0 || j == 0 || i == getWidth()-1 || getLength()-1)
            {
                if(i ==0 && j ==0)                          //northwest corner
                {
                    traversable = false;
                    id = 1;
                    result->insert(std::make_pair(i,j), new Tile(traversable, id));
                }
                else if(i ==this->getLength()-1 && j ==0)   //northeast corner
                {
                    traversable = false;
                    id = 2;
                    result->insert(std::make_pair(i,j), new Tile(traversable, id));
                }
                else if(i == getWidth()-1 && j ==0)         //southwest corner
                {
                    traversable = false;
                    id = 3;

                    result->insert(std::make_pair(i,j), new Tile(traversable, id));
                }
                else if(i == getWidth()-1 && j ==this->getLength()-1) //southeast corner
                {
                    traversable = false;
                    id = 4;
                    result->insert(std::make_pair(i,j), new Tile(traversable, id));
                }
                else if(i ==0)                              //north wall
                {
                    traversable = false;
                    id = 5;
                    result->insert(std::make_pair(i,j), new Tile(traversable, id));
                }
                else if(i ==this->getWidth()-1)             //south wall
                {
                    traversable = false;
                    id = 6;

                    result->insert(std::make_pair(i,j), new Tile(traversable, id));
                }
                else if(j ==0)                              //west wall
                {
                    traversable = false;
                    id = 7;
                    result->insert(std::make_pair(i,j), new Tile(traversable, id));
                }
                else if(j == getLength()-1)                 //east Wall
                {
                    traversable = false;
                    id = 8;
                    result->insert(std::make_pair(i,j), new Tile(traversable, id));
            }
            }
            else                                        //floor
            {
                traversable = true;
                id = 9;
                result->insert(std::make_pair(i,j), new Tile(traversable, id));
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
    result->insert(std::make_pair(0,getWidth()/this->getPreset()), new Tile(traversable, id));
    result->insert(std::make_pair(0,getLength()/this->getPreset()), new Tile(traversable, id));
    result->insert(std::make_pair(getWidth()/this->getPreset(),0), new Tile(traversable, id));
    result->insert(std::make_pair(getLength()/this->getPreset(),0), new Tile(traversable, id));

    traversable = false;
    id = 11;
    //insert chest
    result->insert(std::make_pair(getLength()/this->getPreset()+1,getWidth()/this->getPreset()), new Tile(traversable, id));

    return result;
}


QHash<std::pair<int, int>, Tile*> *GenerateRoom::generateFloor()
{
    bool traversable = true;
    int id = 10;
    QHash<std::pair<int, int>, Tile*> * result = new QHash<std::pair<int, int>, Tile*> ;
    for(int i = 0; i < getLength(); i++){
        for(int j = 0; j < getWidth(); j++){
                result->insert(std::make_pair(i,j), new Tile(traversable, id)); //floor
        }
    }


    return result;
}
