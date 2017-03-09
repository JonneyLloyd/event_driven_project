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

QHash<std::pair<int, int>, int>  *GenerateRoom::generateRoom()
{
    QHash<std::pair<int, int>, int> * result = new QHash<std::pair<int, int>, int> ;
    for(int i = 0; i < getLength(); i++){
        for(int j = 0; j < getWidth(); j++){
            if(i == 0 || j == 0 || i == getWidth()-1 || getLength()-1)
            {
                if(i ==0 && j ==0)                          //northwest corner
                    result->insert(std::make_pair(i,j), 1);
                else if(i ==this->getLength()-1 && j ==0)   //northeast corner
                    result->insert(std::make_pair(i,j), 2);
                else if(i == getWidth()-1 && j ==0)         //southwest corner
                    result->insert(std::make_pair(i,j), 3);
                else if(i == getWidth()-1 && j ==this->getLength()-1) //southeast corner
                    result->insert(std::make_pair(i,j), 4);
                else if(i ==0)                              //north wall
                    result->insert(std::make_pair(i,j), 5);
                else if(i ==this->getWidth()-1)             //south wall
                    result->insert(std::make_pair(i,j), 6);
                else if(j ==0)                              //west wall
                    result->insert(std::make_pair(i,j), 7);
                else if(j == getLength()-1)                 //east Wall
                    result->insert(std::make_pair(i,j), 8);
            }
            else                                        //floor
                result->insert(std::make_pair(i,j), 9);



        }
    }
    return result;
}



QHash<std::pair<int, int>, int> *GenerateRoom::generateItems()
{
    QHash<std::pair<int, int>, int> * result = new QHash<std::pair<int, int>, int> ;

    //inserting 4 doors, pos relative to preset
    result->insert(std::make_pair(0,getWidth()/this->getPreset()), 10);
    result->insert(std::make_pair(0,getLength()/this->getPreset()), 10);
    result->insert(std::make_pair(getWidth()/this->getPreset(),0), 10);
    result->insert(std::make_pair(getLength()/this->getPreset(),0), 10);

    //insert chest
    result->insert(std::make_pair(getLength()/this->getPreset()+1,getWidth()/this->getPreset()), 11);

    return result;
}
