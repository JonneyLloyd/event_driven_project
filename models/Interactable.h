#ifndef INTERACTABLE_H
#define INTERACTABLE_H
#include "TileTypeEnum.h"
#include <QString>

using namespace std;

class Interactable  {

public:
   // pure virtual class
    virtual QString getDescription() const = 0;
    virtual void setDescription(QString value)  = 0;
    virtual QString interact() = 0;
    virtual QString interact(TileType::Enum item) = 0;
};

#endif // INTERACTABLE_H
