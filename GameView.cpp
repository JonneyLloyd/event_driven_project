#include "GameView.h"
#include "Button.h"

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
    this->setScene(&scene);
    //    scene->setSceneRect(0, 0, 800, 600);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFixedSize(800, 600);

    Button * btn = new Button();
    btn->setRect(0, 0, 300, 300);
    scene.addItem(btn);

    player = new PlayerSprite();
    scene.addItem(player);
    player->setPos(300, 300);

}

void GameView::keyPressEvent(QKeyEvent *event)
{
    Direction direction = Direction::NORTH;

    switch (event->key()) {
        case Qt::Key_Up:    direction = Direction::NORTH; break;
        case Qt::Key_Right: direction = Direction::EAST;  break;
        case Qt::Key_Down:  direction = Direction::SOUTH; break;
        case Qt::Key_Left:  direction = Direction::WEST;  break;
        default:            qDebug() << "GameView: KeyEvent ignored"; return;
    }
    qDebug() << "GameView: KeyEvent emitted";
    emit moveEvent(direction);
}

void GameView::movePlayer(Direction direction)
{
    qDebug() << "GameView: Player is moving";
    player->move(direction);
}
