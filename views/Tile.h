#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsObject>


class Tile: public QGraphicsObject
{
    Q_OBJECT

public:
    /*
     * Constructor
     */
    Tile(QPixmap * textureSheet, int tileRow=0, int tileCol=0, int tileSize=16, QGraphicsItem * parent=0);
    ~Tile();

    /*
     * Overrided virtual function
     * Defines the outer bounds of the item as a rectangle
     * All painting happens within these bounds
     */
    QRectF boundingRect() const;

    /*
     * Overrided virtual function
     * Paints/re-paints the tile on update().
     * Non blocking call
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    /*
     * Set the position of the tile on the grid based on the tile size.
     */
    void setGridPos(int x, int y);
    /*
     * Get the position of the tile on the grid based on the tile size.
     */
    int gridX() const;
    /*
     * Set the x position of the tile on the grid based on the tile size.
     */
    void setGridX(int x);
    /*
     * Get the y position of the tile on the grid based on the tile size.
     */
    int gridY() const;
    /*
     * Set the y position of the tile on the grid based on the tile size.
     */
    void setGridY(int y);

    int getTileRow() const;
    void setTileRow(int value);

    int getTileCol() const;
    void setTileCol(int value);

private:
    int tileSize;
    int tileRow;
    int tileCol;

    QPixmap * textureSheet;

};

#endif // TILE_H
