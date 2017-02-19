#ifndef GAMEMENUMAIN_H
#define GAMEMENUMAIN_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPushButton>

class GameMenuMain : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameMenuMain(QObject *parent = 0);
    ~GameMenuMain();

signals:
    void actionStart();

public slots:

private:
    QGraphicsRectItem * rect;
    QPushButton * btn;
};

#endif // GAMEMENUMAIN_H
