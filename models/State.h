#ifndef STATE_H
#define STATE_H

#include "TileTypeEnum.h"
#include "InteractableTile.h"
#include <QHash>


class State
{

public:
    State(QHash<std::pair<int, int>, Tile*> * interactables, std::pair<int, int> roomLocation, int rows, int cols);

    void setInteractables(QHash<std::pair<int, int>, Tile*> * interactables);
    QHash<std::pair<int, int>, Tile*> * getInteractables();
    void setRoomLocation(std::pair<int, int> roomLocation);
    std::pair<int, int> getRoomLocation();
    void setRows(int rows);
    int getRows();
    void setCols(int cols);
    int getCols();

private:
    int rows;
    int cols;
    QHash<std::pair<int, int>, Tile*> * interactables;
    std::pair<int, int> roomLocation;
};


#endif // STATE_H
