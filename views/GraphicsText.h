#ifndef GRAPHICSTEXT_H
#define GRAPHICSTEXT_H

#include <QObject>
#include <QGraphicsLayoutItem>
#include <QGraphicsTextItem>

class GraphicsText: public QGraphicsTextItem, public QGraphicsLayoutItem
{

public:
    GraphicsText(const QString &text, QSize size, QGraphicsItem *parent = 0);

    QRectF boundingRect() const override;

protected:
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;

private:
    QSize size;

};

#endif // GRAPHICSTEXT_H
