#ifndef GRAPHICSINVENTORY_H
#define GRAPHICSINVENTORY_H

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <vector>

#include "TileTypeEnum.h"
#include "views/GraphicsTile.h"


class GraphicsInventory : public QGraphicsWidget
{

public:
    GraphicsInventory(QGraphicsItem *parent = 0);
    ~GraphicsInventory();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void addInventoryItem(int index, TileType tileType);

    void removeInventoryItem(int index);

private:
    int minSize = 4;
    int tileSize = 16;
    int spacing = 4;
    std::vector<GraphicsTile*> items;

    QGraphicsLinearLayout * layout;     // must be a pointer as QGraphicsWidget takes ownership
                                        // (Otherwise segfault on deletion)

};

#endif // GRAPHICSINVENTORY_H
