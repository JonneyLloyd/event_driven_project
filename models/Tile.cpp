#include "Tile.h"


Tile::Tile(bool traversable, TileType id){
    this->traversable = traversable;
    this->id = id;
}

Tile::~Tile()
{

}

void Tile::setTraversabe(bool traversable){
    this->traversable = traversable;
}

void Tile::setId(TileType id){
    this->id = id;
}

bool Tile::getTraversable(){
    return this->traversable;
}

TileType Tile::getId(){
    return this->id;
}


