#ifndef TILE_H
#define TILE_H

#include "TileTypeEnum.h"



class Tile
{

public:
    Tile(bool traversable, TileType id);
    ~Tile();

    void setTraversabe(bool traversable);
    void setId(TileType id);
    bool getTraversable();
    TileType getId();

private:
    bool traversable;
    TileType id;
};



#endif // TILE_H
