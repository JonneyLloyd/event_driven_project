#ifndef INTERACTABLETILE_H
#define INTERACTABLETILE_H
#include "Interactable.h"
#include "Tile.h"


class InteractableTile : public Interactable, public Tile
{
public:
    InteractableTile(QString description, bool traversable, TileType id);
    ~InteractableTile();
    QString getDescription();
    void setDescription(QString value);


protected:
   QString description;

};

#endif // INTERACTABLETILE_H
