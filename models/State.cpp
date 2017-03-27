#include "State.h"


State::State(QHash<std::pair<int, int>, Tile*> * interactables, std::pair<int, int> roomLocation, int rows, int cols)
    :   interactables{interactables},
        roomLocation{roomLocation},
        rows{rows},
        cols{cols}
{
}

void State::setInteractables(QHash<std::pair<int, int>, Tile*> * interactables)
{
    this->interactables = interactables;
}

QHash<std::pair<int, int>, Tile*> * State::getInteractables()
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
