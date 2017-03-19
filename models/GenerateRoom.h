#ifndef GENERATEROOM_H
#define GENERATEROOM_H


#include <QHash>
#include "Tile.h"
#include <QObject>

class GenerateRoom : public QObject
{
    Q_OBJECT
public:
    /*
     * Constructor
     */
    GenerateRoom(int preset, int rows = 16, int columns = 16);
    ~GenerateRoom();
    void setPreset(int preset);
    void setRows(int rows);
    void setColumns(int columns);

    int getPreset();
    int getRows();
    int getColumns();
    void generateRoom();
    void generateFloor();
    void generateDoors();
    QHash<std::pair<int, int>, Tile*> * getFloor();
    QHash<std::pair<int, int>, Tile*> * getWalls();
    QHash<std::pair<int, int>, Tile*> * getDoors();

private:
    int preset;
    int rows;
    int columns;
    QHash<std::pair<int, int>, Tile*>  * floor;
    QHash<std::pair<int, int>, Tile*>  * walls;
    QHash<std::pair<int, int>, Tile*>  * doors;

};




#endif // GENERATEROOM_H
