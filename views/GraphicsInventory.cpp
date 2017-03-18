#include "GraphicsInventory.h"

#include <QPainter>

#include "views/TileLoader.h"

GraphicsInventory::GraphicsInventory(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    layout = new QGraphicsLinearLayout;
    layout->setParentLayoutItem(this);
    this->setLayout(layout);
    layout->setSpacing(spacing);
    layout->setContentsMargins(spacing, spacing, spacing, spacing);
}

GraphicsInventory::~GraphicsInventory()
{
    for (std::vector<GraphicsTile *>::iterator i = items.begin(); i != items.end(); ++i) {
        delete *i;  // Maybe this can be replaced with parenting
    }
}

QRectF GraphicsInventory::boundingRect() const
{
    int cols = std::max(minSize, (int)items.size());
    int width = (tileSize + spacing) * cols + spacing;
    int height = tileSize + spacing * 2;
    return QRectF(0, 0, width, height);
}

void GraphicsInventory::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(QColor(47,60,78), Qt::SolidPattern));
    painter->setPen(QColor(200,60,78));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRoundedRect(this->boundingRect(), 2, (tileSize + spacing * 2)/2);
}

void GraphicsInventory::addInventoryItem(int index, TileType tileType)
{
    TileLoader tileLoader = TileLoader::getInstance();
    auto tile = tileLoader.get(tileType);
    tile->setParentLayoutItem(layout);  // needed?
    items.insert(items.begin() + index, tile);
    layout->insertItem(index, tile);
}

void GraphicsInventory::removeInventoryItem(int index)
{
    auto tile = items[index];
    layout->removeItem(tile);  // needed?
    items.erase(items.begin() + index);
    delete tile;

}


// TODO:
// When adding this place it in the middle of a horizontal layout
// Style it
// Add boxes for the items
// Click listeners??
