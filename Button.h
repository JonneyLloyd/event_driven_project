#ifndef MYRECT_H
#define MYRECT_H

#include <QtGui>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

class Button: public QObject, public QGraphicsRectItem {
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

signals:
    void clicked();
};

#endif // MYRECT_H
