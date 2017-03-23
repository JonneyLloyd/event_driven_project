#include "GraphicsInventoryItem.h"


GraphicsInventoryItem::GraphicsInventoryItem(int size, int spacing, QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      size{size},
      spacing{spacing}
{
    layout = new QGraphicsLinearLayout(this);
    setLayout(layout);
    layout->setContentsMargins(spacing, spacing, spacing, spacing);
    setAcceptHoverEvents(true);
}

GraphicsInventoryItem::~GraphicsInventoryItem()
{
    delete layout->itemAt(0);
}

QRectF GraphicsInventoryItem::boundingRect() const
{
    return QRectF(0, 0, size, size);
}

void GraphicsInventoryItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->drawRect(this->geometry());
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(QColor(47,60,78), Qt::SolidPattern));
    painter->setPen(*activeColor);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRoundedRect(this->boundingRect(), 2, 2);
}

void GraphicsInventoryItem::setGraphicsTile(GraphicsTile * tile)
{
    layout->insertItem(0, tile);
}

void GraphicsInventoryItem::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        emit itemClickedEvent(this);
    }
}

void GraphicsInventoryItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    activeColor = &hoverColor;
    update();
}

void GraphicsInventoryItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    activeColor = &defaultColor;
    update();
}
