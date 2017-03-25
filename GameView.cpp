#include "GameView.h"
#include "Button.h"
#include "TileTypeEnum.h"
#include "views/TileLoader.h"
#include <QDebug>

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
    setScene(&scene);
//    scene.setSceneRect(0, 0, 16*30, 9*30);
    initScene();


    // Note: the above classes are only visual representations, all logic should reside in models

    // TODO (views):
    //  Introduce layering
    //  Draw map/layers using model output - there is a method to do all painting in one go
    //  Add menu widgets
    //  Figure out if QGraphicsItem * parent is needed/wanted and adjust tile objects (since it is the last param)
    //  Fix memory problems!!

    // TODO (models):
    //  Representations for player, interactable objects, world, layers, tiles
    //  Provide this to the view in an easy to consume way?
    //  Block keyboard input while player is moving
    //  Validate player moves
    //  Check if the tile in front can be interacted with (activated, walked on)
    //  Move rooms
    //  Blocking calls/game loop

}

void GameView::initScene()
{
    scene.clear();
    fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundBrush(QBrush(QColor(47,40,58), Qt::SolidPattern));

    Button * btn = new Button();
    btn->setRect(0, 0, 16, 16);
    scene.addItem(btn);

    initPlayer();
    initInventory();
    fitInView(scene.sceneRect(), Qt::KeepAspectRatio);

    // temp
    testInitAnimation();
}

GameView::~GameView()
{

}



void GameView::initPlayer()
{
    TileLoader tileLoader = TileLoader::getInstance();
    player = qgraphicsitem_cast<PlayerSprite*>(tileLoader.get(TileType::PLAYER));
    scene.addItem(player);
    player->setGridPos(10, 4);
    player->setZValue(1);
}

void GameView::initInventory()
{
    inventory = new GraphicsInventory;
    inventory->setPos(16*5, 16*14);
    inventory->setScale(1.2);
    scene.addItem(inventory);
    connect(inventory, SIGNAL(inventoryItemClickedEvent(int)), SIGNAL(inventoryClickEvent(int)));
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    Direction direction = Direction::NORTH;

    switch (event->key()) {
        case Qt::Key_Up:    direction = Direction::NORTH; break;
        case Qt::Key_Right: direction = Direction::EAST;  break;
        case Qt::Key_Down:  direction = Direction::SOUTH; break;
        case Qt::Key_Left:  direction = Direction::WEST;  break;

        case Qt::Key_Return: emit interact();
        case Qt::Key_1: case Qt::Key_2: case Qt::Key_3: case Qt::Key_4:
        case Qt::Key_5: case Qt::Key_6: case Qt::Key_7: case Qt::Key_8:
        case Qt::Key_9:     emit inventoryClickEvent(event->text().toInt() - 1);
                            return;

        default:            qDebug() << "GameView: KeyEvent ignored"; return;
    }
    emit moveEvent(direction);
}

void GameView::movePlayer(Direction direction)
{
    qDebug() << "GameView: Player is moving";
    player->move(direction);

    // temp
    testAnimation();
}

void GameView::displayFloor(QHash<std::pair<int, int>, Tile *> * floor,
                            QHash<std::pair<int, int>, Tile *> * walls,
                            QHash<std::pair<int, int>, Tile *> * doors)
{

    initScene();
    TileLoader tileLoader = TileLoader::getInstance();
    GraphicsTile * tile;
    QHash<std::pair<int, int>, Tile*>::iterator i;
    for (i = floor->begin(); i != floor->end(); ++i){
        tile = tileLoader.get(i.value()->getId());
        //z value shows previous layers when moving room. Working on fix
        tile->setZValue(-1);  // temp, everything may be added to a 'layer/group' (maybe use enums rather than numbers?): http://stackoverflow.com/questions/18074798/layers-on-qgraphicsview
        scene.addItem(tile);
        tile->setGridPos(i.key().first, i.key().second);
    }

    for (i = walls->begin(); i != walls->end(); ++i){
        tile = tileLoader.get(i.value()->getId());
        tile->setGridPos(i.key().first, i.key().second);
        scene.addItem(tile);
    }

    for (i = doors->begin(); i != doors->end(); ++i) {
        tile = tileLoader.get(i.value()->getId());
        scene.addItem(tile);
        tile->setGridPos(i.key().first, i.key().second);
    }
    //TODO resetting player in center
    player->setGridPos(10, 4);
}

void GameView::addInventoryItem(int index, TileType type)
{
    inventory->addInventoryItem(index, type);
}

void GameView::removeInventoryItem(int index)
{
    inventory->removeInventoryItem(index);
}

// temp
void GameView::testInitAnimation()
{
    TileLoader tileLoader = TileLoader::getInstance();

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
}

void GameView::testAnimation()
{
    static int n = 0;
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile)->start(n%2 == 0 ? false:true);
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile2)->start(n%2 == 0 ? false:true);
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile3)->start(n%2 == 0 ? false:true);
    n++;
}
