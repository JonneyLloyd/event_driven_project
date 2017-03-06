#include "AnimatedTile.h"

AnimatedTile::AnimatedTile(QPixmap *textureSheet, int tileRow, int tileCol, int numberOfFrames, int duration, int tileSize, QGraphicsItem *parent)
    : Tile(textureSheet, tileRow, tileCol, tileSize, parent),
      numberOfFrames{numberOfFrames},
      initialTileCol{tileCol}
{
    timeLine = new QTimeLine();
    setDuration(duration);
    setNumberOfFramesPerAnimation(numberOfFrames);
    timeLine->setCurveShape(QTimeLine::CurveShape::LinearCurve);
    QObject::connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(onFrameChanged(int)));
}

AnimatedTile::~AnimatedTile()
{
    delete timeLine;
}

void AnimatedTile::start(bool reverse)
{
    timeLine->setDirection(reverse ? QTimeLine::Direction::Backward : QTimeLine::Direction::Forward);
    timeLine->start();
}

void AnimatedTile::setDuration(int value)
{
    timeLine->setDuration(value);
    timeLine->setCurrentTime(value);  // required to avoid a known bug skipping frames
}

void AnimatedTile::setLoopCount(int value)
{
    timeLine->setLoopCount(value);
}

void AnimatedTile::setNumberOfFrames(int value)
{
    numberOfFrames = value;
}

void AnimatedTile::setNumberOfFramesPerAnimation(int value)
{
    timeLine->setFrameRange(0, value - 1);
}

void AnimatedTile::onFrameChanged(int frame)
{
    this->setTileCol(initialTileCol + frame % this->numberOfFrames);
    this->update(this->boundingRect());
}
