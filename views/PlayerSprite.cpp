#include "PlayerSprite.h"


PlayerSprite::PlayerSprite(QSharedPointer<QPixmap> textureSheet, QGraphicsItem * parent)
    : AnimatedGraphicsTile(textureSheet, 0, 0, 3, 500, 16, parent)
{
    setNumberOfFramesPerAnimation(4);
}

PlayerSprite::~PlayerSprite()
{

}

void PlayerSprite::move(Direction::Enum direction)
{
    setHeading(direction);
    start();
}

void PlayerSprite::setHeading(Direction::Enum direction)
{
    spriteDirection = direction;
    setTileRow(spriteOffset[spriteDirection]);
    update();
}

void PlayerSprite::onFrameChanged(int frame)
{
    int moveAmt = 16 / 4;    // i.e. moving 16px with 4 frames
    switch (spriteDirection) {
        case Direction::NORTH:  setPos(x(),             y() - moveAmt); break;
        case Direction::EAST:   setPos(x() + moveAmt,   y());           break;
        case Direction::SOUTH:  setPos(x(),             y() + moveAmt); break;
        case Direction::WEST:   setPos(x() - moveAmt,   y());           break;
        default: break;
    }
    AnimatedGraphicsTile::onFrameChanged(frame);
}
