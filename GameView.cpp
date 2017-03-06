#include "GameView.h"
#include "Button.h"

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
    this->setScene(&scene);
    scene.setSceneRect(0, 0, 16*30, 9*30);
    this->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    Button * btn = new Button();
    btn->setRect(0, 0, 16, 16);
    scene.addItem(btn);

    door = new DoorSprite();
    scene.addItem(door);
    door->setPos(16*22, 16*4);
    door->open();

    player = new PlayerSprite();
    scene.addItem(player);
    player->setPos(16*22, 16*4);


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

    door->open();   // TODO: move to separate slot when model has logic to emit a signal to the controller
}
