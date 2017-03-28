#ifndef STATE_H
#define STATE_H

#include "TileTypeEnum.h"
#include "InteractableTile.h"
#include <QHash>


class State
{

public:
    State(std::pair<int, int> roomLocation, int rows, int cols, QHash<TileType::Enum, TileType::Enum> interactables);

    void setInteractables(QHash<TileType::Enum, TileType::Enum> interactables);
    QHash<TileType::Enum, TileType::Enum> getInteractables();
    void setRoomLocation(std::pair<int, int> roomLocation);
    std::pair<int, int> getRoomLocation();
    void setRows(int rows);
    int getRows();
    void setCols(int cols);
    int getCols();
    void changeInteractable(TileType::Enum interactable, TileType::Enum newKey);


private:
    int rows;
    int cols;
    QHash<TileType::Enum, TileType::Enum> interactables;
    std::pair<int, int> roomLocation;
};


#endif // STATE_H
