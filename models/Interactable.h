#ifndef INTERACTABLE_H
#define INTERACTABLE_H
#include "TileTypeEnum.h"
#include <QString>

using namespace std;

class Interactable  {

public:
   // pure virtual class
    virtual QString getDescription() = 0;
    virtual void setDescription(QString value)  = 0;
    virtual TileType getType() = 0;
    virtual void setType(TileType value) = 0;

protected:
   QString description;
   TileType type;
};

#endif // INTERACTABLE_H
