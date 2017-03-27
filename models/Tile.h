#ifndef TILE_H
#define TILE_H

#include "TileTypeEnum.h"



class Tile
{

public:
    Tile(bool traversable, TileType::Enum id);
    ~Tile();

    void setTraversabe(bool traversable);
    void setId(TileType::Enum id);
    bool getTraversable();
    TileType::Enum getId();

private:
    bool traversable;
    TileType::Enum id;
};



#endif // TILE_H
