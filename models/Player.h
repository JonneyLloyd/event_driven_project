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
    void setHeading(Direction heading);
    Direction getHeading();
    int getX() const;
    int getY() const;


private:
    int x;
    int y;
    Direction heading;
};

#endif // PLAYER_H
