#ifndef INTERACTABLETILE_H
#define INTERACTABLETILE_H
#include "Interactable.h"
#include "Tile.h"


class InteractableTile : public Interactable, public Tile
{
public:
    InteractableTile(QString description, bool traversable, TileType::Enum id, bool state, TileType::Enum key);
    InteractableTile(QString description, bool traversable, TileType::Enum id, bool state);
    InteractableTile(QString description, bool traversable, TileType::Enum id);
    ~InteractableTile();
    QString getDescription();
    void setDescription(QString value);
    void setState(bool state);
    bool getState();
    void setKey(TileType::Enum value);
    TileType::Enum getKey();
    QString interact();
    QString interact(TileType::Enum item);


protected:
   QString description;
   bool state;
   TileType::Enum key;

};

#endif // INTERACTABLETILE_H
