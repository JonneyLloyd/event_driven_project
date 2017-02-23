#include "player.h"
#include <QImage>



Player::Player(int defaultMove, int size, QString pixMapLocation, QGraphicsItem *parent)
{
    move = defaultMove;

    QImage sprite_sheet(pixMapLocation);
    spriteDown = sprite_sheet.copy(0, 0, 32, 32);
    spriteUp = sprite_sheet.copy(0, 96, 32, 32);
    spriteLeft = sprite_sheet.copy(0, 128, 32, 32);
    spriteRight = sprite_sheet.copy(0, 32, 32, 32);


    this->setPixmap(QPixmap::fromImage(spriteDown));
}


Player::~Player()
{

}

void Player::setPosition(int x, int y)
{
    this->setPixmap(QPixmap::fromImage(spriteDown));
    setPos(x, y);
}

void Player::moveLeft()
{
    this->setPixmap(QPixmap::fromImage(spriteLeft));
    setPos(x() - move, y());
}

void Player::moveRight()
{
    this->setPixmap(QPixmap::fromImage(spriteRight));
    setPos(x() + move, y());
}

void Player::moveUp()
{
    this->setPixmap(QPixmap::fromImage(spriteUp));
    setPos(x(), y() - move);
}

void Player::moveDown()
{
    this->setPixmap(QPixmap::fromImage(spriteDown));
    setPos(x(), y() + move);
}

