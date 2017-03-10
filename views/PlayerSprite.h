#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include <vector>

#include "views/AnimatedGraphicsTile.h"
#include "DirectionEnum.h"

class PlayerSprite : public AnimatedGraphicsTile
{
    Q_OBJECT

public:
    /*
     * Constructor
     * params not needed as they are tied to the sprite sheet anyway
     */
     PlayerSprite(QPixmap * textureSheet, QGraphicsItem * parent=0);
    ~PlayerSprite();

    /*
     * Move one step in the given direction
     */
    void move(Direction direction);

    void onFrameChanged(int frame);

private:
    Direction spriteDirection = Direction::SOUTH;             // The initial heading
    std::vector<int> spriteOffset = {2, 1, 0, 3};       // The positional offset in of each sprite
                                                        // facing north, east, south, west

};

#endif // PLAYERSPRITE_H
