#include <QPainter>

#include "PlayerSprite.h"

#include <QDebug>

// Consider tile and/or sprite classes

// Source:
// http://stackoverflow.com/questions/24401281/how-to-animat-a-qpixmap-in-qt
// http://doc.qt.io/qt-4.8/qtimeline.html#details

PlayerSprite::PlayerSprite(QGraphicsItem *parent)
{
    sprite_sheet = new QPixmap(":/sprite_sheets/res/sprite_sheets/knight_anim_sheet.png");

    timeLine = new QTimeLine(1000);
    timeLine->setFrameRange(0, spriteFramesPerAnimation);
    timeLine->setCurveShape(QTimeLine::CurveShape::LinearCurve);
    QObject::connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(animatedMove(int)));

}

PlayerSprite::~PlayerSprite()
{
    delete timeLine;
    delete sprite_sheet;
}

QRectF PlayerSprite::boundingRect() const
{
    return QRectF(0, 0, spriteSize, spriteSize);
}

void PlayerSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *sprite_sheet,                        // x, y position, sprite sheet
                        spriteFrame*spriteSize,                     // col,
                        spriteOffset[spriteDirection]*spriteSize,   // row of sprite sheet
                        spriteSize, spriteSize);                    // width, height
}

void PlayerSprite::move(Direction direction)
{
    spriteDirection = direction;
    timeLine->start();
}

void PlayerSprite::animatedMove(int frame)
{
    qDebug() << "Frame: " << frame << "  " << frame % numberOfFrames;
    int moveAmt = spriteSize / spriteFramesPerAnimation;    // i.e. moving 32px with 8 frames
                                                            // => move 32/8=4 pixels per frame
    switch (spriteDirection) {
        case Direction::NORTH:  setPos(x(),             y() - moveAmt); break;
        case Direction::EAST:   setPos(x() + moveAmt,   y());           break;
        case Direction::SOUTH:  setPos(x(),             y() + moveAmt); break;
        case Direction::WEST:   setPos(x() - moveAmt,   y());           break;
    }
    spriteFrame = frame % numberOfFrames;   // set the current frame for painting
    this->update(boundingRect());           // Non blocking repaint
}

