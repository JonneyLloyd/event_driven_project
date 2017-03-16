#ifndef GRAPHICSINVENTORY_H
#define GRAPHICSINVENTORY_H

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <vector>

#include "TileTypeEnum.h"
#include "views/GraphicsTile.h"


class GraphicsInventory : public QGraphicsWidget // public QGraphicsLinearLayout, public QGraphicsObject
{

public:
    GraphicsInventory();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addInventoryItem(int index, TileType tileType);

    void removeInventoryItem(int index);

private:
    int minSize = 4;
    int tileSize = 16;
    int spacing = 4;
    std::vector<GraphicsTile*> items;

    QGraphicsLinearLayout layout;

};

#endif // GRAPHICSINVENTORY_H
