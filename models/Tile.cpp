#include "Tile.h"


Tile::Tile(bool traversable, int id){
    this->traversable = traversable;
    this->id = id;
}

Tile::~Tile()
{

}

void Tile::setTraversabe(bool traversable){
    this->traversable = traversable;
}

void Tile::setId(int id){
    this->id = id;
}

bool Tile::getTraversable(){
    return this->traversable;
}

int Tile::getId(){
    return this->id;
}


