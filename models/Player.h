#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(int x,int y);
    ~Player();

    void setX(int x);
    void setY(int y);
    void setXY(int x, int y);
    int getX() const;
    int getY() const;

private:
    int x;
    int y;
};

#endif // PLAYER_H
