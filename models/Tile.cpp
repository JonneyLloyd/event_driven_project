#include "Tile.h"


Tile::Tile(bool traversable, TileType::Enum id){
    this->traversable = traversable;
    this->id = id;
}

Tile::~Tile()
{

}

void Tile::setTraversabe(bool traversable){
    this->traversable = traversable;
}

void Tile::setId(TileType::Enum id){
    this->id = id;
}

bool Tile::getTraversable(){
    return this->traversable;
}

TileType::Enum Tile::getId(){
    return this->id;
}


