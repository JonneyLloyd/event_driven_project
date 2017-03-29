#ifndef STATE_H
#define STATE_H

#include "TileTypeEnum.h"
#include "InteractableTile.h"
#include <QHash>


class State
{

public:
    State(std::pair<int, int> roomLocation, int rows, int cols,
          QHash<TileType::Enum, TileType::Enum> interactableContent,
          QHash<TileType::Enum, bool> interactableState);
    void setInteractableContent(QHash<TileType::Enum, TileType::Enum> interactableContent);
    QHash<TileType::Enum, TileType::Enum> getInteractableContent();
    QHash<TileType::Enum, bool> getInteractableState();
    void setRoomLocation(std::pair<int, int> roomLocation);
    std::pair<int, int> getRoomLocation();
    void setRows(int rows);
    int getRows();
    void setCols(int cols);
    int getCols();
    void changeInteractableContent(TileType::Enum interactable, TileType::Enum newKey);
    void changeInteractableContent(TileType::Enum interactable, bool newState);

private:
    int rows;
    int cols;
    QHash<TileType::Enum, TileType::Enum> interactableContent;
    QHash<TileType::Enum, bool> interactableState;
    std::pair<int, int> roomLocation;
};


#endif // STATE_H
