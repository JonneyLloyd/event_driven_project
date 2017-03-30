#ifndef GRAPHICSMENUITEM_H
#define GRAPHICSMENUITEM_H

#include <QObject>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsSceneMouseEvent>

#include <QPainter>

#include "views/GraphicsTile.h"


class GraphicsMenuItem: public QGraphicsWidget
{
    Q_OBJECT

public:
    GraphicsMenuItem(QSize size, int margin, QGraphicsItem *parent = 0);
    ~GraphicsMenuItem();

    QRectF boundingRect() const override;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setGraphicsLayoutItem(QGraphicsLayoutItem * layoutItem);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

signals:
    void itemClickedEvent(const GraphicsMenuItem * child);

private:
    QSize size;
    int margin;
    QColor defaultColor = QColor(37,50,68);
    QColor hoverColor = QColor(145,176,154);
    QColor * activeColor = &defaultColor;
    QGraphicsLinearLayout * layout;     // must be a pointer as QGraphicsWidget takes ownership
                                        // (Otherwise segfault on deletion)

};

#endif // GRAPHICSMENUITEM_H
