#include <QPainter>

#include "views/DoorSprite.h"

#include <QDebug>

// Consider tile and/or sprite classes

// Source:
// http://stackoverflow.com/questions/24401281/how-to-animat-a-qpixmap-in-qt
// http://doc.qt.io/qt-4.8/qtimeline.html#details

DoorSprite::DoorSprite(QGraphicsItem *parent)
{
    sprite_sheet = new QPixmap(":/sprite_sheets/res/sprite_sheets/dungeon_sheet.png");

    timeLine = new QTimeLine(500);
    timeLine->setFrameRange(0, spriteFramesPerAnimation-1);  // TODO
    timeLine->setCurveShape(QTimeLine::CurveShape::LinearCurve);
    QObject::connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(animatedMove(int)));

}

DoorSprite::~DoorSprite()
{
    delete timeLine;
    delete sprite_sheet;
}

QRectF DoorSprite::boundingRect() const
{
    return QRectF(0, 0, spriteSize, spriteSize);
}

void DoorSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(boundingRect());
    painter->drawPixmap(0, 0, *sprite_sheet,                        // x, y position, sprite sheet
                        spriteFrame*spriteSize,                     // col,
                        spriteOffset*spriteSize,   // row of sprite sheet
                        spriteSize, spriteSize);                    // width, height
}

void DoorSprite::open()
{
    timeLine->start();
}

void DoorSprite::animatedMove(int frame)
{// TODO
    spriteFrame = frame % numberOfFrames + 4;   // set the current frame for painting
    this->update(boundingRect());           // Non blocking repaint
}

