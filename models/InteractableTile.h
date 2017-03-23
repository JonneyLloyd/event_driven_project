#ifndef INTERACTABLETILE_H
#define INTERACTABLETILE_H
#include "Interactable.h"
#include "Tile.h"


class InteractableTile : public Interactable, public Tile
{
public:
    InteractableTile(QString description, TileType type, bool traversable, TileType id);
    ~InteractableTile();
    QString getDescription();
    void setDescription(QString value);
    TileType getType();
    void setType(TileType value);

protected:
   QString description;
   TileType type;
};

#endif // INTERACTABLETILE_H
