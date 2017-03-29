#include "State.h"


State::State(std::pair<int, int> roomLocation, int rows, int cols,
             QHash<TileType::Enum, TileType::Enum> interactableContent,
             QHash<TileType::Enum, bool> interactableState)
    : roomLocation{roomLocation},
      rows{rows},
      cols{cols},
      interactableContent{interactableContent},
      interactableState{interactableState}
{
}

void State::setInteractableContent(QHash<TileType::Enum, TileType::Enum> interactableContent)
{
    this->interactableContent = interactableContent;
}

QHash<TileType::Enum, TileType::Enum> State::getInteractableContent()
{
    return this->interactableContent;
}

QHash<TileType::Enum, bool> State::getInteractableState()
{
    return this->interactableState;
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

void State::changeInteractableContent(TileType::Enum interactable, TileType::Enum newKey)
{
    QHash<TileType::Enum, TileType::Enum>::iterator i;
    i = interactableContent.find(interactable);
    i.value() = newKey;
}

void State::changeInteractableContent(TileType::Enum interactable, bool newState)
{
    QHash<TileType::Enum, bool>::iterator i;
    i = interactableState.find(interactable);
    i.value() = newState;
}
