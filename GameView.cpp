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


    QPixmap * textureSheet = new QPixmap(":/sprite_sheets/res/sprite_sheets/dungeon_sheet.png");
    // Example of loading a basic tile (since behaviour of e.g. floor and walls never changes they can use the same class)
    testTile = new Tile(textureSheet, 7, 8);
    scene.addItem(testTile);
    testTile->setPos(16*2, 16*2);

    // on/off or opened/closed objects should probably be wrapped in their own classes or at least a StateAnimatedTile
    testAnimatedTile = new AnimatedTile(textureSheet, 7, 8, 6);
    scene.addItem(testAnimatedTile);
    testAnimatedTile->setPos(16*4, 16*2);

    // Note: the above classes are only visual representations, all logic should reside in models

    // TODO (views):
    //  Add setGridPos to abstract away coordinates in favour of tile units
    //  Modify Door and Player to use new Tile classes
    //  Add singleton resource loaders for both sprite sheets so as not to pass them everywhere, optionally use it from within specific classes
    //  Introduce layering
    //  Draw map/layers using model output - there is a method to do all painting in one go
    //  Add menu widgets

    // TODO (models):
    //  Representations for player, interactable objects, world, layers, tiles
    //  Provide this to the view in an easy to consume way?
    //  Block keyboard input while player is moving
    //  Validate player moves
    //  Check if the tile in front can be interacted with (activated, walked on)
    //  Move rooms


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

    // temp
    door->open();   // TODO: move to separate slot when model has logic to emit a signal to the controller
    testAnimatedTile->start();
}
