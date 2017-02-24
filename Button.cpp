#include "Button.h"

void Button::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton) {
        qDebug() << "clicked";
        emit clicked();
    }
}
