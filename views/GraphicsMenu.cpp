#include "GraphicsMenu.h"

#include <QPainter>

#include "views/TileLoader.h"

// TODO: Oliver operator overloading?
GraphicsMenu::GraphicsMenu(Qt::Orientation orientation, QSize childSize, int minSize, int margin, int childMargin, QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      minSize{minSize},
      childMargin{childMargin},
      childSize{childSize}
{
    layout = new QGraphicsLinearLayout(orientation, this);
    setLayout(layout);
    layout->setSpacing(margin);
    layout->setContentsMargins(margin, margin, margin, margin);
}

GraphicsMenu::~GraphicsMenu()
{
    for (int i = layout->count()-1; i >=0; i--) {
        delete layout->itemAt(i);
    }
}

QRectF GraphicsMenu::boundingRect() const
{
    int cols = std::max(minSize, (int)layout->count());
    int height = 0, width = 0;
    if (layout->orientation() == Qt::Orientation::Horizontal) {
        width = (getChildBoundingSize().width() + layout->spacing()) * cols + layout->spacing();
        height = getChildBoundingSize().height() + 2*layout->spacing();
    }
    else if (layout->orientation() == Qt::Orientation::Vertical) {
        height = (getChildBoundingSize().height() + layout->spacing()) * cols + layout->spacing();
        width = getChildBoundingSize().width() + 2*layout->spacing();
    }
    return QRectF(0, 0, width, height);
}

void GraphicsMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(QColor(47,60,78), Qt::SolidPattern));
    painter->setPen(QColor(200,60,78));
    painter->setRenderHint(QPainter::Antialiasing);
    if (layout->orientation() == Qt::Orientation::Horizontal)
        painter->drawRoundedRect(boundingRect(), 2, getChildBoundingSize().height()/2);
    else if (layout->orientation() == Qt::Orientation::Vertical)
        painter->drawRoundedRect(boundingRect(), getChildBoundingSize().width()/2, 2);
}

void GraphicsMenu::addInventoryItem(int index, QGraphicsLayoutItem * layoutItem)
{
    auto widgetItem = new GraphicsMenuItem(getChildBoundingSize(), getChildLayoutMargin(), this);
    connect(widgetItem, SIGNAL(itemClickedEvent(GraphicsMenuItem*)), SLOT(itemClicked(GraphicsMenuItem*)));
    widgetItem->setGraphicsLayoutItem(layoutItem);
    layout->insertItem(index, widgetItem);
}

void GraphicsMenu::removeInventoryItem(int index)
{
    prepareGeometryChange();
    delete layout->itemAt(index);
    update();
}

void GraphicsMenu::itemClicked(GraphicsMenuItem *child)
{
    for(int i = 0; i < layout->count(); i++) {
        if (layout->itemAt(i) == child) {
            emit inventoryItemClickedEvent(i);
        }
    }
}

int GraphicsMenu::getChildLayoutMargin() const
{
    return childMargin;
}

QSize GraphicsMenu::getChildSize() const
{
    return childSize;
}

QSize GraphicsMenu::getChildBoundingSize() const
{
    int width = getChildSize().width() + 2*getChildLayoutMargin();
    int height = getChildSize().height() + 2*getChildLayoutMargin();
    return QSize(width, height);
}
