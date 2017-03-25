#include "Player.h"


Player::Player(int x, int y)
{
    this->x = x;
    this->y = y;
}


Player::~Player()
{

}


void Player::setX(int x)
{
    this->x = x;
}


void Player::setY(int y)
{
    this->y = y;
}


void Player::setXY(int x, int y)
{
    setX(x);
    setY(y);
}


int Player::getX()
{
    return this->x;
}


int Player::getY()
{
    return this->y;
}

void Player::setHeading(Direction heading)
{
    this->heading = heading;
}

Direction Player::getHeading()
{
    return this->heading;
}
