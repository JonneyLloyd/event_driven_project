#ifndef DOORSPRITE_H
#define DOORSPRITE_H

#include <QObject>
#include <QGraphicsObject>
#include <QTimeLine>
#include <QString>
#include <vector>


class DoorSprite: public QGraphicsObject
{
    Q_OBJECT

public:
    /*
     * Constructor
     * params not needed as they are tied to the sprite sheet anyway
     */
     DoorSprite(QGraphicsItem * parent=0);
    ~DoorSprite();

    /*
     * Open the door
     */
    void open();

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
    int spriteSize = 16;    // Width and height of the sprite, amount sprite moves in one step
    int spriteFramesPerAnimation = 4;   // Animate with 4 frames
    int spriteFrame = 4;                                // The current frame of the animation
    int numberOfFrames = 4;                             // Number of frames in the sprite sheet
    int spriteOffset = {7};       // The positional offset in of each sprite
                                                        // facing north, east, south, west

    QPixmap * sprite_sheet;     // Source of sprite
    QTimeLine * timeLine;       // Periodically emits signals to asynchronously animate

private slots:
    /*
     * Prepares each frame of the animation
     */
    void animatedMove(int frame);

};


#endif // DOORSPRITE_H
