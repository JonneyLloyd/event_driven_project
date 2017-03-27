#ifndef GRAPHICSMENUPAUSEBUTTON_H
#define GRAPHICSMENUPAUSEBUTTON_H

#include <QtGui>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

class GraphicsMenuPauseButton: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

signals:
    void clickEvent();

private:
    const QColor backgroundColor = QColor(47,60,78);
    const QColor borderColor = QColor(37,50,68);
    const QColor accentColor = QColor(200,60,78);

};

#endif // GRAPHICSMENUPAUSEBUTTON_H
