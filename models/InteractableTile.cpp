#include "InteractableTile.h"


InteractableTile::InteractableTile(QString description, bool traversable, TileType id)
    : Tile(traversable, id),
      description{description}
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





