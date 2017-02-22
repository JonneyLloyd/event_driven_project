#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QString>
#include <QImage>



class Player:  public QGraphicsPixmapItem {

public:
     Player(int defaultMove, int size, QString pixMapLocation, QGraphicsItem * parent=0);
    ~Player();

    void setPosition(int x, int y);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
private:
    int move = 0;
    QImage spriteUp;
    QImage spriteDown;
    QImage spriteLeft;
    QImage spriteRight;
};


#endif // PLAYER_H
