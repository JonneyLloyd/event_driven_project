#include "AnimatedGraphicsTile.h"

AnimatedGraphicsTile::AnimatedGraphicsTile(QSharedPointer<QPixmap> textureSheet, int tileRow, int tileCol, int numberOfFrames, int duration, int tileSize, QGraphicsItem *parent)
    : GraphicsTile(textureSheet, tileRow, tileCol, tileSize, parent),
      numberOfFrames{numberOfFrames},
      initialTileCol{tileCol}
{
    setDuration(duration);
    setNumberOfFramesPerAnimation(numberOfFrames);
    timeLine.setCurveShape(QTimeLine::CurveShape::LinearCurve);
    QObject::connect(&timeLine, SIGNAL(frameChanged(int)), this, SLOT(onFrameChanged(int)));
}

void AnimatedGraphicsTile::start(bool reverse)
{
    timeLine.setDirection(reverse ? QTimeLine::Direction::Backward : QTimeLine::Direction::Forward);
    timeLine.start();
}

void AnimatedGraphicsTile::setDuration(int value)
{
    timeLine.setDuration(value);
    timeLine.setCurrentTime(value);  // required to avoid a known bug skipping frames
}

void AnimatedGraphicsTile::setLoopCount(int value)
{
    timeLine.setLoopCount(value);
}

void AnimatedGraphicsTile::setNumberOfFrames(int value)
{
    numberOfFrames = value;
}

void AnimatedGraphicsTile::setNumberOfFramesPerAnimation(int value)
{
    timeLine.setFrameRange(0, value - 1);
}

void AnimatedGraphicsTile::onFrameChanged(int frame)
{
    this->setTileCol(initialTileCol + frame % this->numberOfFrames);
    this->update(this->boundingRect());
}
