#include "InteractableTile.h"


InteractableTile::InteractableTile(QString description, TileType type, bool traversable, TileType id)
    : Tile(traversable, id),
      description{description},
      type{type}
{
}


InteractableTile::~InteractableTile()
{

}


QString InteractableTile::getDescription()
{
    return this->description;
}


void InteractableTile::setDescription(QString value)
{
    this->description = value;
}


TileType InteractableTile::getType()
{
    return this->type;
}


void InteractableTile::setType(TileType value)
{
    this->type = value;
}




