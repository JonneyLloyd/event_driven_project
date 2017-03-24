#include "InteractableTile.h"


InteractableTile::InteractableTile(QString description, bool traversable, TileType id, bool state, TileType key)
    :   Tile(traversable, id),
        description{description},
        state{state},
        key{key}
{
}

InteractableTile::InteractableTile(QString description, bool traversable, TileType id, bool state)
    :   Tile(traversable, id),
        description{description},
        state{state},
        key{TileType::EMPTY}
{
}

InteractableTile::InteractableTile(QString description, bool traversable, TileType id)
    :   Tile(traversable, id),
        description{description},
        state{true}
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

void InteractableTile::setState(bool state)
{
    this->state = state;
}

bool InteractableTile::getState()
{
    return this->state;
}

void InteractableTile::setKey(TileType value)
{
    this->key = value;
}

TileType InteractableTile::getKey()
{
    return this->key;
}

QString InteractableTile::interact()
{
    if (this->key != TileType::EMPTY)
        return this->description;
    else
    {
        this->state = !state;
        return "It worked";
    }
}

QString InteractableTile::interact(TileType item)
{
    if (this->key == item)
    {
        this->state = !state;
        return "It worked";
    }
    else
        return this->description;
}





