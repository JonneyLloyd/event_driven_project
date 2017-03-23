#ifndef GRAPHICSINVENTORYITEM_H
#define GRAPHICSINVENTORYITEM_H

#include <QObject>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsSceneMouseEvent>

#include <QPainter>

#include "views/GraphicsTile.h"


class GraphicsInventoryItem: public QGraphicsWidget
{
    Q_OBJECT

public:
    GraphicsInventoryItem(int size, int spacing, QGraphicsItem *parent = 0);
    ~GraphicsInventoryItem();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setGraphicsTile(GraphicsTile * tile);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

signals:
    void itemClickedEvent(GraphicsInventoryItem * child);

private:
    int size;
    int spacing;
//    QColor defaultColor = QColor(200,60,78);
    QColor defaultColor = QColor(37,50,68);
    QColor hoverColor = QColor(145,176,154);
    QColor * activeColor = &defaultColor;
    QGraphicsLinearLayout * layout;     // must be a pointer as QGraphicsWidget takes ownership
                                        // (Otherwise segfault on deletion)

};

#endif // GRAPHICSINVENTORYITEM_H
