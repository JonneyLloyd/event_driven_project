#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPushButton>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = 0);

signals:
    void actionQuit();

public slots:

private:
    QGraphicsRectItem * rect;
    QPushButton * btn;
};

#endif // GAMESCENE_H
