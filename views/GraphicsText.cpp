#include "GraphicsText.h"

#include <QPainter>

GraphicsText::GraphicsText(const QString &text, QSize size, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent),
      size{size}
{
    setGraphicsItem(this);
    setDefaultTextColor(QColor(200,60,78));
    setFont(QFont("calibri", 5));
}

QRectF GraphicsText::boundingRect() const
{
    return QRectF(QPointF(0,0), geometry().size());
}

QSizeF GraphicsText::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);
    return size;
}
