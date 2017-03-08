#include <QPainter>

#include "GraphicsTile.h"

GraphicsTile::GraphicsTile(QPixmap * textureSheet, int tileRow, int tileCol, int tileSize, QGraphicsItem *parent)
    : textureSheet{textureSheet},
      tileSize{tileSize},
      tileRow{tileRow},
      tileCol{tileCol}
{

}

GraphicsTile::~GraphicsTile()
{

}

QRectF GraphicsTile::boundingRect() const
{
    return QRectF(0, 0, tileSize, tileSize);
}

void GraphicsTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *textureSheet,    // x, y position, sprite sheet
                        tileCol*tileSize,       // col,
                        tileRow*tileSize,       // row of sprite sheet
                        tileSize, tileSize);    // width, height
}

void GraphicsTile::setGridPos(int x, int y)
{
    setPos(x * tileSize, y * tileSize);
}

int GraphicsTile::gridX() const
{
    return (int) x() / tileSize;
}

void GraphicsTile::setGridX(int x)
{
    setX(x * tileSize);
}

int GraphicsTile::gridY() const
{
    return (int) y() / tileSize;
}

void GraphicsTile::setGridY(int y)
{
    setX(y * tileSize);
}

int GraphicsTile::getTileRow() const
{
    return tileRow;
}

void GraphicsTile::setTileRow(int value)
{
    tileRow = value;
}

int GraphicsTile::getTileCol() const
{
    return tileCol;
}

void GraphicsTile::setTileCol(int value)
{
    tileCol = value;
}
