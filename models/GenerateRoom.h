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
    GenerateRoom(int preset, int length = 16, int width = 16);
    ~GenerateRoom();
    void setPreset(int preset);
    void setLength(int length);
    void setWidth(int width);

    int getPreset();
    int getLength();
    int getWidth();
    QHash<std::pair<int, int>, Tile*> *generateRoom();
    QHash<std::pair<int, int>, Tile*> *generateItems();
    QHash<std::pair<int, int>, Tile*> *generateFloor();


private:
    int preset;
    int length;
    int width;

};




#endif // GENERATEROOM_H
