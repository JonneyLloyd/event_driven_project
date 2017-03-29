#ifndef GENERATEROOM_H
#define GENERATEROOM_H


#include <QHash>
#include "InteractableTile.h"

class GenerateRoom
{
public:
    /*
     * Constructor
     */
    GenerateRoom(int rows = 16, int columns = 16);
    ~GenerateRoom();
    void setRows(int rows);
    void setColumns(int columns);
    int getRows()  const;
    int getColumns()  const;
    void generateRoom();
    void generateFloor();
    void generateDoors();
    void generateInteractableLayer(QHash<TileType::Enum, TileType::Enum> interactableList,
                                   QHash<TileType::Enum, bool> interactableState);
    QHash<std::pair<int, int>, Tile*> * getFloor()  const;
    QHash<std::pair<int, int>, Tile*> * getWalls()  const;
    QHash<std::pair<int, int>, Tile*> * getInteractables()  const;
    std::pair<int, int> getTileCoords(TileType::Enum tileName)  const;

private:
    int rows;
    int columns;
    QHash<std::pair<int, int>, Tile*>  * floor;
    QHash<std::pair<int, int>, Tile*>  * walls;
    QHash<std::pair<int, int>, Tile*>  * interactables;
    QHash<std::pair<int, int>, InteractableTile*>  * interactableDoors;
};




#endif // GENERATEROOM_H
