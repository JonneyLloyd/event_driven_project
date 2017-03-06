#include <QPainter>

#include "Tile.h"

Tile::Tile(QPixmap * textureSheet, int tileRow, int tileCol, int tileSize, QGraphicsItem *parent)
    : textureSheet{textureSheet},
      tileSize{tileSize},
      tileRow{tileRow},
      tileCol{tileCol}
{

}

Tile::~Tile()
{

}

QRectF Tile::boundingRect() const
{
    return QRectF(0, 0, tileSize, tileSize);
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, *textureSheet,    // x, y position, sprite sheet
                        tileCol*tileSize,       // col,
                        tileRow*tileSize,       // row of sprite sheet
                        tileSize, tileSize);    // width, height
}

int Tile::getTileRow() const
{
    return tileRow;
}

void Tile::setTileRow(int value)
{
    tileRow = value;
}

int Tile::getTileCol() const
{
    return tileCol;
}

void Tile::setTileCol(int value)
{
    tileCol = value;
}
