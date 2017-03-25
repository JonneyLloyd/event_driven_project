#ifndef INTERACTABLETILE_H
#define INTERACTABLETILE_H
#include "Interactable.h"
#include "Tile.h"


class InteractableTile : public Interactable, public Tile
{
public:
    InteractableTile(QString description, bool traversable, TileType id, bool state, TileType key);
    InteractableTile(QString description, bool traversable, TileType id, bool state);
    InteractableTile(QString description, bool traversable, TileType id);
    ~InteractableTile();
    QString getDescription();
    void setDescription(QString value);
    void setState(bool state);
    bool getState();
    void setKey(TileType value);
    TileType getKey();
    QString interact();
    QString interact(TileType item);


protected:
   QString description;
   bool state;
   TileType key;

};

#endif // INTERACTABLETILE_H
