#include "Tile.h"


Tile::Tile(bool traversable, TileType::Enum id){
    this->traversable = traversable;
    this->id = id;
}

void Tile::setTraversabe(bool traversable){
    this->traversable = traversable;
}

void Tile::setId(TileType::Enum id){
    this->id = id;
}

bool Tile::getTraversable() const{
    return this->traversable;
}

TileType::Enum Tile::getId() const{
    return this->id;
}


