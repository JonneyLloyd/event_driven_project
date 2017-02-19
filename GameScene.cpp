#include "gamescene.h"
#include <QGraphicsScene>

GameScene::GameScene(QObject *parent) : QGraphicsScene(parent)
{
    // Create Rectangle
    rect = new QGraphicsRectItem();
    rect->setRect(20, 50, 200, 120);
    this->addItem(rect);

    btn = new QPushButton(QString("Test2"));
    this->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), SIGNAL(actionQuit()));
}
