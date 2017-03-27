#include "GraphicsMenuItem.h"


GraphicsMenuItem::GraphicsMenuItem(QSize size, int margin, QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      size{size},
      margin{margin}
{
    layout = new QGraphicsLinearLayout(this);
    setLayout(layout);
    layout->setContentsMargins(margin, margin, margin, margin);
    setAcceptHoverEvents(true);
}

GraphicsMenuItem::~GraphicsMenuItem()
{
    delete layout->itemAt(0);
}

QRectF GraphicsMenuItem::boundingRect() const
{
    return QRectF(0, 0, size.width(), size.height());
}

QSizeF GraphicsMenuItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);
    return QSize(size.width(), size.height());
}

void GraphicsMenuItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(QColor(47,60,78), Qt::SolidPattern));
    painter->setPen(*activeColor);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRoundedRect(this->boundingRect(), 2, 2);
}

void GraphicsMenuItem::setGraphicsLayoutItem(QGraphicsLayoutItem *layoutItem)
{
    layout->insertItem(0, layoutItem);
}

void GraphicsMenuItem::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        activeColor = &defaultColor;
        emit itemClickedEvent(this);
    }
}

void GraphicsMenuItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    activeColor = &hoverColor;
    update();
}

void GraphicsMenuItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    activeColor = &defaultColor;
    update();
}
