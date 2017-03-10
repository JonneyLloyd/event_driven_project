#ifndef GENERATEROOM_H
#define GENERATEROOM_H


#include <QHash>
#include "Tile.h"

class GenerateRoom
{

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
    QHash<std::pair<int, int>, Tile*> *generateRoom();
    QHash<std::pair<int, int>, Tile*> *generateItems();
    QHash<std::pair<int, int>, Tile*> *generateFloor();


private:
    int preset;
    int rows;
    int columns;

};




#endif // GENERATEROOM_H
