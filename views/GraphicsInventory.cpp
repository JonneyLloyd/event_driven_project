#include "GraphicsInventory.h"

#include <QPainter>

#include "views/TileLoader.h"

#include <QDebug>


GraphicsInventory::GraphicsInventory(int minSize, int tileSize, int spacing, QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      minSize{minSize},
      tileSize{tileSize},
      spacing{spacing}
{
    layout = new QGraphicsLinearLayout(this);
    setLayout(layout);
    layout->setSpacing(spacing);
    layout->setContentsMargins(spacing, spacing, spacing, spacing);
}

GraphicsInventory::~GraphicsInventory()
{
    for (int i = layout->count()-1; i >=0; i--) {
        delete layout->itemAt(i);
    }
}

QRectF GraphicsInventory::boundingRect() const
{
    int cols = std::max(minSize, (int)layout->count());
    int width = (getChildSize() + spacing) * cols + spacing;
    int height = getChildSize() + spacing * 2;
    return QRectF(0, 0, width, height);
}

void GraphicsInventory::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(QColor(47,60,78), Qt::SolidPattern));
    painter->setPen(QColor(200,60,78));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRoundedRect(boundingRect(), 2, (tileSize + spacing * 2)/2);
}

void GraphicsInventory::addInventoryItem(int index, TileType tileType)
{
    TileLoader tileLoader = TileLoader::getInstance();
    auto tile = tileLoader.get(tileType);
    auto item = new GraphicsInventoryItem(getChildSize(), getChildSpacing());
    connect(item, SIGNAL(itemClickedEvent(GraphicsInventoryItem*)), SLOT(itemClicked(GraphicsInventoryItem*)));
    item->setGraphicsTile(tile);
//    tile->setParentLayoutItem(layout);  // needed?
    layout->insertItem(index, item);
}

void GraphicsInventory::removeInventoryItem(int index)
{
    prepareGeometryChange();
    delete layout->itemAt(index);
    update();
}

void GraphicsInventory::itemClicked(GraphicsInventoryItem *child)
{
    for(int i = 0; i < layout->count(); i++) {
        if (layout->itemAt(i) == child) {
            emit inventoryItemClickedEvent(i);
        }
    }
}

int GraphicsInventory::getChildSpacing() const
{
    return spacing/2;
}

int GraphicsInventory::getChildSize() const
{
    return tileSize + 2*getChildSpacing();
}


// TODO:
// When adding this place it in the middle of a horizontal layout
// Style it
// Add boxes for the items
// Click listeners??
// Fix parenting
