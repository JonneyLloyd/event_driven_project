#include "Player.h"


Player::Player(int x, int y)
{
    this->x = x;
    this->y = y;
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


int Player::getX() const
{
    return this->x;
}


int Player::getY() const
{
    return this->y;
}


void Player::setHeading(Direction::Enum heading)
{
    this->heading = heading;
}


Direction::Enum Player::getHeading()
{
    return this->heading;
}
