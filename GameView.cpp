#include "GameView.h"
#include "GraphicsMenuPauseButton.h"
#include "TileTypeEnum.h"
#include "views/TileLoader.h"
#include "views/GraphicsText.h"
#include "LayerEnum.h"
#include <QDebug>

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
    setScene(&scene);
//    scene.setSceneRect(0, 0, 16*30, 9*30);
    initScene();
    fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundBrush(QBrush(QColor(47,40,58), Qt::SolidPattern));

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

    GraphicsMenuPauseButton * pauseButton = new GraphicsMenuPauseButton();
    pauseButton->setRect(0, 0, 16, 16);
    pauseButton->setPos(-20, 0);
    scene.addItem(pauseButton);
    connect(pauseButton, SIGNAL(clickEvent()), SIGNAL(pauseClickEvent()));

    initPlayer();
    initInventory();
    initMenu();

    // temp
    //testInitAnimation();
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
    player->setZValue(Layer::PLAYER);
}

void GameView::initInventory()
{
    inventory = new GraphicsMenu(Qt::Orientation::Horizontal, QSize(16, 16));
    inventory->setPos(16*5, 16*14);
    inventory->setScale(1.2);
    inventory->setZValue(Layer::GUI_BACKGROUND);
    scene.addItem(inventory);
    connect(inventory, SIGNAL(inventoryItemClickedEvent(int)), SIGNAL(inventoryClickEvent(int)));
}

void GameView::initMenu()
{
    menu = new GraphicsMenu(Qt::Orientation::Vertical, QSize(40, 10), 2, 8);
    menu->hide();
    menu->setPos(16*7, 16*3);
    menu->setScale(1.5);
    menu->setZValue(Layer::GUI_FOREGROUND);
    scene.addItem(menu);
    connect(menu, SIGNAL(inventoryItemClickedEvent(int)), SIGNAL(menuClickEvent(int)));
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up: case Qt::Key_W:    emit moveEvent(Direction::NORTH); break;
        case Qt::Key_Right: case Qt::Key_D: emit moveEvent(Direction::EAST);  break;
        case Qt::Key_Down: case Qt::Key_S:  emit moveEvent(Direction::SOUTH); break;
        case Qt::Key_Left: case Qt::Key_A:  emit moveEvent(Direction::WEST);  break;

        case Qt::Key_Escape: emit pauseClickEvent(); break;
        case Qt::Key_Space: case Qt::Key_Return: emit interactEvent(); break;
        case Qt::Key_1: case Qt::Key_2: case Qt::Key_3: case Qt::Key_4:
        case Qt::Key_5: case Qt::Key_6: case Qt::Key_7: case Qt::Key_8:
        case Qt::Key_9:     emit inventoryClickEvent(event->text().toInt() - 1); break;

        default:            qDebug() << "GameView: KeyEvent ignored"; return;
    }
}

void GameView::movePlayer(Direction::Enum direction)
{
    player->move(direction);

    // temp
    //testAnimation();
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

        tile->setZValue(Layer::BACKGROUND);  // temp, everything may be added to a 'layer/group' (maybe use enums rather than numbers?): http://stackoverflow.com/questions/18074798/layers-on-qgraphicsview
        tile->setGridPos(i.key().first, i.key().second);
        scene.addItem(tile);
    }

    for (i = walls->begin(); i != walls->end(); ++i){
        tile = tileLoader.get(i.value()->getId());
        tile->setZValue(Layer::MIDDLEGROUND);
        tile->setGridPos(i.key().first, i.key().second);
        scene.addItem(tile);
    }

    for (i = doors->begin(); i != doors->end(); ++i) {
        tile = tileLoader.get(i.value()->getId());
        tile->setZValue(Layer::INTERACTABLE);
        tile->setGridPos(i.key().first, i.key().second);
        scene.addItem(tile);
    }
}

void GameView::addInventoryItem(int index, TileType::Enum type)
{
    TileLoader tileLoader = TileLoader::getInstance();
    auto tile = tileLoader.get(type);
    inventory->addInventoryItem(index, tile);
}

void GameView::removeInventoryItem(int index)
{
    inventory->removeInventoryItem(index);
}

void GameView::setPlayerLocation(int x, int y)
{
    player->setGridPos(x, y);
    qDebug() << "setPos signal received";
}

void GameView::setPlayerHeading(Direction::Enum direction)
{
    player->setHeading(direction);
}

void GameView::displayMenu(bool visible)
{
    if (visible)
        menu->show();
    else
        menu->hide();
}

void GameView::addMenuItem(int index, QString text)
{
    auto item = new GraphicsText(text, QSize(40, 10));
    menu->addInventoryItem(index, item);
}



// temp
void GameView::testInitAnimation()
{
    TileLoader tileLoader = TileLoader::getInstance();

    // on/off or opened/closed objects should probably be wrapped in their own classes or at least a StateAnimatedTile
    testAnimatedTile = tileLoader.get(TileType::CHEST);
    scene.addItem(testAnimatedTile);
    testAnimatedTile->setGridPos(4, 2);
    testAnimatedTile->setZValue(Layer::INTERACTABLE);

    testAnimatedTile2 = tileLoader.get(TileType::SWITCH);
    scene.addItem(testAnimatedTile2);
    testAnimatedTile2->setGridPos(7, 2);
    testAnimatedTile2->setZValue(Layer::INTERACTABLE);

    testAnimatedTile3 = tileLoader.get(TileType::DOOR);
    scene.addItem(testAnimatedTile3);
    testAnimatedTile3->setGridPos(7, 6);
    testAnimatedTile3->setZValue(Layer::INTERACTABLE);


//    for (int t = DOOR; t <= ORB_GREY; t++) {
//        GraphicsTile * tile = tileLoader.get(static_cast<TileType>(t));
//        scene.addItem(tile);
//        tile->setGridPos(t, 12);
//    }
}

void GameView::testAnimation()
{
    static int n = 0;
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile)->start(n%2 == 0 ? false:true);
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile2)->start(n%2 == 0 ? false:true);
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile3)->start(n%2 == 0 ? false:true);
    n++;
}
