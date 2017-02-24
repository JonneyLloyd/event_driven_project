#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsObject>
#include <QTimeLine>
#include <QString>
#include <vector>

#include "DirectionEnum.h"


class PlayerSprite: public QGraphicsObject
{
    Q_OBJECT

public:
    /*
     * Constructor
     * params not needed as they are tied to the sprite sheet anyway
     */
     PlayerSprite(QGraphicsItem * parent=0);
    ~PlayerSprite();

    /*
     * Move one step in the given direction
     */
    void move(Direction direction);

    /*
     * Overrided virtual function
     * Defines the outer bounds of the item as a rectangle
     * All painting happens within these bounds
     */
    QRectF boundingRect() const;

    /*
     * Overrided virtual function
     * Paints/re-paints the sprite on update().
     * Non blocking call
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    int spriteSize = 32;    // Width and height of the sprite, amount sprite moves in one step
    int spriteFramesPerAnimation = 8;   // Animate with 8 frames
    int spriteFrame = 0;                                // The current frame of the animation
    int numberOfFrames = 3;                             // Number of frames in the sprite sheet
    Direction spriteDirection = Direction::SOUTH;             // The initial heading
    std::vector<int> spriteOffset = {3, 1, 0, 4};       // The positional offset in of each sprite
                                                        // facing north, east, south, west

    QPixmap * sprite_sheet;     // Source of sprite
    QTimeLine * timeLine;       // Periodically emits signals to asynchronously animate

private slots:
    /*
     * Prepares each frame of the animation
     */
    void animatedMove(int frame);

};


#endif // PLAYER_H
