#include <QPainter>

#include "GraphicsTile.h"

GraphicsTile::GraphicsTile(QPixmap * textureSheet, int tileRow, int tileCol, int tileSize, QGraphicsItem *parent)
    : textureSheet{textureSheet},
      tileSize{tileSize},
      tileRow{tileRow},
      tileCol{tileCol},
      traversable{traversable}
{
    setGraphicsItem(this);
    this->setGeometry(QRectF(0, 0, tileSize, tileSize));
}

GraphicsTile::~GraphicsTile()
{

}

//QRectF GraphicsTile::boundingRect() const
//{
//    return QRectF(0, 0, tileSize, tileSize);
//}

QRectF GraphicsTile::boundingRect() const
{
    return QRectF(QPointF(0,0), geometry().size());
}

void GraphicsTile::setGeometry(const QRectF &geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

QSizeF GraphicsTile::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    return QSize(tileSize, tileSize);
//    switch ( which )
//    {
//        case Qt::MinimumSize:
//        case Qt::PreferredSize:
//            return QSizeF(tileSize, tileSize);

//        case Qt::MaximumSize:
//            return QSizeF(tileSize*2, tileSize*2);

//        default:
//            return this->boundingRect().size();
//    }

//    return constraint;
}

void GraphicsTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->drawRect(this->boundingRect());
    painter->drawPixmap(0, 0, this->geometry().width(), this->geometry().height(), *textureSheet,    // x, y position, sprite sheet
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

bool GraphicsTile::getTraversable()
{
    return traversable;
}

void GraphicsTile::setTraversable(bool value)
{
    traversable = value;
}
