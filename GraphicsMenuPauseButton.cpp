#include "GraphicsMenuPauseButton.h"

void GraphicsMenuPauseButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QBrush(backgroundColor, Qt::SolidPattern));
    painter->setPen(borderColor);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRoundedRect(this->boundingRect(), 2, 2);

    painter->setBrush(QBrush(accentColor, Qt::SolidPattern));
    painter->setPen(accentColor);

    int width = boundingRect().width();
    int height = boundingRect().height();

    int y = height/4;
    int w = width/8;
    int h = height/2;
    int r = 1;

    painter->drawRoundedRect(QRect(width/3, y, w, h), r, r);
    painter->drawRoundedRect(QRect(width-(width/3 + width/8), y, w, h), r, r);
}

void GraphicsMenuPauseButton::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        emit clickEvent();
    }
}
