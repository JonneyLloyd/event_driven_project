#ifndef GRAPHICSMENU_H
#define GRAPHICSMENU_H

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>

#include "views/GraphicsMenuItem.h"


class GraphicsMenu : public QGraphicsWidget
{
    Q_OBJECT

public:
    GraphicsMenu(Qt::Orientation orientation, QSize childSize, int minSize = 4, int margin = 4, int childMargin = 2, QGraphicsItem *parent = 0);
    ~GraphicsMenu();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void addInventoryItem(int index, QGraphicsLayoutItem * layoutItem);
    void removeInventoryItem(int index);

private slots:
    void itemClicked(const GraphicsMenuItem *child);

signals:
    void inventoryItemClickedEvent(int index);

private:
    inline int getChildLayoutMargin() const;
    inline QSize getChildSize() const;
    inline QSize getChildBoundingSize() const;

    int minSize;
    int childMargin;
    QSize childSize;

    QGraphicsLinearLayout * layout;

};

#endif // GRAPHICSMENU_H
