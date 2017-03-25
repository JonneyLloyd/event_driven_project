#ifndef PLAYER_H
#define PLAYER_H

#include "DirectionEnum.h"

class Player
{
public:
    Player(int x,int y);
    ~Player();

    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    int getX();
    int getY();
    void setHeading(Direction heading);
    Direction getHeading();

private:
    int x;
    int y;
    Direction heading;
};

#endif // PLAYER_H
