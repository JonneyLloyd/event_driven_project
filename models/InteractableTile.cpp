#include "InteractableTile.h"


InteractableTile::InteractableTile(QString description, bool traversable, TileType::Enum id, bool state, TileType::Enum key)
    :   Tile(traversable, id),
        description{description},
        state{state},
        key{key}
{
}

InteractableTile::InteractableTile(QString description, bool traversable, TileType::Enum id, bool state)
    :   Tile(traversable, id),
        description{description},
        state{state},
        key{TileType::EMPTY}
{
}

InteractableTile::InteractableTile(QString description, bool traversable, TileType::Enum id)
    :   Tile(traversable, id),
        description{description},
        state{true},
        key{TileType::EMPTY}
{
}

QString InteractableTile::getDescription()  const
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

bool InteractableTile::getState()  const
{
    return this->state;
}

void InteractableTile::setKey(TileType::Enum value)
{
    this->key = value;
}

TileType::Enum InteractableTile::getKey()  const
{
    return this->key;
}

QString InteractableTile::interact()
{
    if (this->key == TileType::EMPTY)
      this->state = true;
    return this->description;
}

QString InteractableTile::interact(TileType::Enum item)
{
    QString result = "";
    if (this->key == item)
    {
        //interaction successful so switch state
        this->state = !state;
        if(!state)
            result = "That closed it";
        else
            result = "That opened it";
    }
    else
        result = "That didnt work!";
    return result;
}





