#ifndef ANIMATEDTILE_H
#define ANIMATEDTILE_H

#include "views/Tile.h"

#include <QTimeLine>

class AnimatedTile : public Tile
{
    Q_OBJECT

public:
    AnimatedTile(QPixmap * textureSheet, int tileRow=0, int tileCol=0, int numberOfFrames=1, int duration=500, int tileSize=16, QGraphicsItem * parent=0);
    ~AnimatedTile();

    void start(bool reverse=false);

    void setDuration(int value);

    void setLoopCount(int value);

    void setNumberOfFrames(int value);

    void setNumberOfFramesPerAnimation(int value);

private:
    int numberOfFrames;
    int currentFrame;
    int initialTileCol;

    QTimeLine * timeLine;

public slots:
    void onFrameChanged(int frame);

};

#endif // ANIMATEDTILE_H
