#ifndef TILE_H
#define TILE_H



class Tile
{

public:
    Tile(bool traversable, int id);
    ~Tile();

    void setTraversabe(bool traversable);
    void setId(int id);
    bool getTraversable();
    int getId();

private:
    bool traversable;
    int id;
};



#endif // TILE_H
