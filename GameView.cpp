#include "GameView.h"
#include "Button.h"
#include "views/TileLoader.h"
#include "TileTypeEnum.h"
#include "models/GenerateRoom.h"
//#include <QHash>

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
    this->setScene(&scene);
    scene.setSceneRect(0, 0, 16*30, 9*30);
    this->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setBackgroundBrush(QBrush(QColor(47,40,58), Qt::SolidPattern));

    Button * btn = new Button();
    btn->setRect(0, 0, 16, 16);
    scene.addItem(btn);

    door = new DoorSprite();
    scene.addItem(door);
    door->setPos(16*22, 16*4);
    door->open();




    TileLoader tileLoader = TileLoader::getInstance();

    QPixmap * textureSheet = new QPixmap(":/sprite_sheets/res/sprite_sheets/dungeon_sheet.png");
    // Example of loading a basic tile (since behaviour of e.g. floor and walls never changes they can use the same class)
    testTile = new GraphicsTile(textureSheet, 7, 8);
    scene.addItem(testTile);
    testTile->setPos(16*2, 16*2);

    GraphicsTile * wall = new GraphicsTile(textureSheet, 0, 5);
    scene.addItem(wall);
    wall->setPos(16*10, 16*10);

    //testing map
    //just generating floor for now
    //not sure why yet but seems to be splitting floor into even squares
    GenerateRoom * test = new GenerateRoom(2,32,16);
    QHash<std::pair<int, int>, Tile*> * result = test->generateFloor();

    QHash<std::pair<int, int>, Tile*>::iterator i;
    for (i = result->begin(); i != result->end(); ++i){
        if(i.value()->getId()==9){
            GraphicsTile * floor = new GraphicsTile(textureSheet, 2, 6);
            scene.addItem(floor);
            floor->setPos(16*i.key().first, 16*i.key().second);
        }

    }

    player = new PlayerSprite();
    scene.addItem(player);
    player->setPos(16*22, 16*4);

    // on/off or opened/closed objects should probably be wrapped in their own classes or at least a StateAnimatedTile
    testAnimatedTile = tileLoader.get(TileType::CHEST);
    scene.addItem(testAnimatedTile);
    testAnimatedTile->setGridPos(4, 2);

    testAnimatedTile2 = tileLoader.get(TileType::SWITCH);
    scene.addItem(testAnimatedTile2);
    testAnimatedTile2->setGridPos(7, 2);

    testAnimatedTile3 = tileLoader.get(TileType::DOOR);
    scene.addItem(testAnimatedTile3);
    testAnimatedTile3->setGridPos(7, 6);

    for (int t = DOOR; t <= ORB_GREY; t++) {
        GraphicsTile * tile = tileLoader.get(static_cast<TileType>(t));
        scene.addItem(tile);
        tile->setGridPos(t, 12);
    }

    // Note: the above classes are only visual representations, all logic should reside in models

    // TODO (views):
    //  Modify Door and Player to use new Tile classes
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
    static int n = 0;
    door->open();   // TODO: move to separate slot when model has logic to emit a signal to the controller
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile)->start(n%2 == 0 ? false:true);
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile2)->start(n%2 == 0 ? false:true);
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile3)->start(n%2 == 0 ? false:true);
    n++;
}
