#ifndef TILELOADER_H
#define TILELOADER_H

#include <QSharedPointer>
#include <QPixmap>

#include "TileTypeEnum.h"
#include "views/GraphicsTile.h"

/*
 * Singleton class containing the necessary texture/sprite sheets.
 * Builds the correct Tile or AnimatedTile based on the tile type requested.
 */
class TileLoader
{

public:
    static TileLoader & getInstance();
    GraphicsTile * get(const TileType::Enum & tileType) const;

    // Prevent copies of the singleton
    TileLoader(TileLoader const &) = delete;        // Delete copy constructor
    void operator=(TileLoader const &)  = delete;   // Delete copy assignment operator

private:
    TileLoader();

    // Smart pointers ensure these images are available to clients even after the singleton is deleted
    QSharedPointer<QPixmap> textureSheet;
    QSharedPointer<QPixmap> spriteSheet;

};

#endif // TILELOADER_H
