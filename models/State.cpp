#include "State.h"


State::State(std::pair<int, int> roomLocation, int rows, int cols,
             QHash<TileType::Enum, TileType::Enum> interactables)
    : roomLocation{roomLocation},
      rows{rows},
      cols{cols},
      interactables{interactables}
{
}

void State::setInteractables(QHash<TileType::Enum, TileType::Enum> interactables)
{
    this->interactables = interactables;
}

QHash<TileType::Enum, TileType::Enum> State::getInteractables()
{
    return this->interactables;
}

void State::setRoomLocation(std::pair<int, int> roomLocation)
{
    this->roomLocation = roomLocation;
}

std::pair<int, int> State::getRoomLocation()
{
    return this->roomLocation;
}

void State::setRows(int rows)
{
    this->rows = rows;
}

int State::getRows()
{
    return this->rows;
}

void State::setCols(int cols)
{
    this->cols = cols;
}

int State::getCols()
{
    return this->cols;
}

void State::changeInteractable(TileType::Enum interactable, TileType::Enum newKey)
{
    QHash<TileType::Enum, TileType::Enum>::iterator i;
    i = interactables.find(interactable);
    i.value() = newKey;
}
