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
    QHash<std::pair<int, int>, Tile*> * getFloor();
    QHash<std::pair<int, int>, Tile*> * getWalls();

private:
    int preset;
    int rows;
    int columns;
    QHash<std::pair<int, int>, Tile*>  * floor;
    QHash<std::pair<int, int>, Tile*>  * walls;


};




#endif // GENERATEROOM_H
