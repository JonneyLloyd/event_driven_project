#ifndef GRAPHICSINVENTORY_H
#define GRAPHICSINVENTORY_H

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>

#include "TileTypeEnum.h"
#include "views/GraphicsTile.h"
#include "views/GraphicsInventoryItem.h"


class GraphicsInventory : public QGraphicsWidget
{
    Q_OBJECT

public:
    GraphicsInventory(int minSize = 4, int tileSize = 16, int spacing = 4, QGraphicsItem *parent = 0);
    ~GraphicsInventory();

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void addInventoryItem(int index, TileType tileType);

    void removeInventoryItem(int index);

private slots:
    void itemClicked(GraphicsInventoryItem * child);

signals:
    void inventoryItemClickedEvent(int index);

private:
    inline int getChildSpacing() const;
    inline int getChildSize() const;

    int minSize;
    int tileSize;
    int spacing;

    QGraphicsLinearLayout * layout;

};

#endif // GRAPHICSINVENTORY_H
