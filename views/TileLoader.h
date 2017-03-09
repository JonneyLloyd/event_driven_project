#ifndef TILELOADER_H
#define TILELOADER_H

#include <QPixmap>

#include "TileTypeEnum.h"
#include "views/GraphicsTile.h"
#include "views/AnimatedGraphicsTile.h"

/*
 * Singleton class containing the necessary texture/sprite sheets.
 * Builds the correct Tile or AnimatedTile based on the tile type requested.
 */
class TileLoader
{

public:
    static TileLoader & getInstance();
    GraphicsTile * get(TileType tileType) const;

private:
    TileLoader();
    QPixmap * textureSheet;
    QPixmap * spriteSheet;

};

#endif // TILELOADER_H
