#include "PlayerSprite.h"


PlayerSprite::PlayerSprite(QSharedPointer<QPixmap> textureSheet, QGraphicsItem * parent)
    : AnimatedGraphicsTile(textureSheet, 0, 0, 3, 500, 16, parent)
{
    setNumberOfFramesPerAnimation(4);
}

PlayerSprite::~PlayerSprite()
{

}

void PlayerSprite::move(Direction direction)
{
    spriteDirection = direction;
    setTileRow(spriteOffset[spriteDirection]);
    start();
}

void PlayerSprite::onFrameChanged(int frame)
{

//    qDebug() << "Frame: " << frame << "  " << frame % numberOfFrames;
//    int moveAmt = spriteSize / spriteFramesPerAnimation;    // i.e. moving 32px with 8 frames
    int moveAmt = 16 / 4;    // i.e. moving 32px with 8 frames
                                                            // => move 32/8=4 pixels per frame
    switch (spriteDirection) {
        case Direction::NORTH:  setPos(x(),             y() - moveAmt); break;
        case Direction::EAST:   setPos(x() + moveAmt,   y());           break;
        case Direction::SOUTH:  setPos(x(),             y() + moveAmt); break;
        case Direction::WEST:   setPos(x() - moveAmt,   y());           break;
    }
    AnimatedGraphicsTile::onFrameChanged(frame);
}
