#include "GameView.h"
#include "GraphicsMenuPauseButton.h"
#include "TileTypeEnum.h"
#include "views/TileLoader.h"
#include "views/GraphicsText.h"
#include "LayerEnum.h"
#include <QDebug>

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
    interactables = new QHash<std::pair<int, int>, GraphicsTile *>();
    setScene(&scene);
    initScene();
    fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundBrush(QBrush(QColor(47,40,58), Qt::SolidPattern));

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
}

GameView::~GameView()
{
    // All variables/objects on the heap have been added to the scene.
    // the scene takes ownership of these objects and calls there destructors
    // when cleared or when terminated.
}



void GameView::initPlayer()
{
    TileLoader & tileLoader = TileLoader::getInstance();
    player = qgraphicsitem_cast<PlayerSprite*>(tileLoader.get(TileType::PLAYER));
    scene.addItem(player);
    player->setGridPos(10, 4);
    player->setZValue(Layer::PLAYER);
}

void GameView::initInventory()
{
    inventory = new GraphicsMenu(Qt::Orientation::Horizontal, QSize(16, 16));
    inventory->setPos(16*4+6, 16*12);
    inventory->setScale(1.2);
    inventory->setZValue(Layer::GUI_BACKGROUND);
    scene.addItem(inventory);
    connect(inventory, SIGNAL(inventoryItemClickedEvent(int)), SIGNAL(inventoryClickEvent(int)));
}

void GameView::initMenu()
{
    menu = new GraphicsMenu(Qt::Orientation::Vertical, QSize(40, 10), 2, 8);
    menu->hide();
    menu->setPos(16*5+5, 16*2);
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
}

void GameView::displayFloor(QHash<std::pair<int, int>, Tile *> * floor,
                            QHash<std::pair<int, int>, Tile *> * walls,
                            QHash<std::pair<int, int>, Tile *> * doors)
{

    initScene();
    TileLoader & tileLoader = TileLoader::getInstance();
    QHash<std::pair<int, int>, Tile*>::iterator i;
    for (i = floor->begin(); i != floor->end(); ++i){
        auto tile = tileLoader.get(i.value()->getId());
        tile->setZValue(Layer::BACKGROUND);
        tile->setGridPos(i.key().first, i.key().second);
        scene.addItem(tile);
    }

    for (i = walls->begin(); i != walls->end(); ++i){
        auto tile = tileLoader.get(i.value()->getId());
        tile->setZValue(Layer::MIDDLEGROUND);
        tile->setGridPos(i.key().first, i.key().second);
        scene.addItem(tile);

        GraphicsTile * tileDeco = nullptr;
        if (i.value()->getId() == TileType::WALL_N_L) {
            tileDeco = tileLoader.get(TileType::WALL_N_U);
        }
        else if (i.value()->getId() == TileType::WALL_NE_CORNER_L) {
            tileDeco = tileLoader.get(TileType::WALL_NE_CORNER_U);
        }
        else if (i.value()->getId() == TileType::WALL_NW_CORNER_L) {
            tileDeco = tileLoader.get(TileType::WALL_NW_CORNER_U);
        }

        if (tileDeco != nullptr) {
            tileDeco->setZValue(Layer::MIDDLEGROUND);
            tileDeco->setGridPos(i.key().first, i.key().second - 1);
            scene.addItem(tileDeco);
        }
    }

    for (i = doors->begin(); i != doors->end(); ++i) {
        auto tile = tileLoader.get(i.value()->getId());
        tile->setZValue(Layer::INTERACTABLE);
        tile->setGridPos(i.key().first, i.key().second);
        scene.addItem(tile);
        interactables->insert(std::make_pair(i.key().first, i.key().second), tile);
    }
}

void GameView::setInteractableItemState(const std::pair<int, int> & position, bool activated, int loopCount)
{
    auto tile = interactables->value(position);
    if (AnimatedGraphicsTile * x = dynamic_cast<AnimatedGraphicsTile*>(tile)) {
        x->setLoopCount(loopCount);
        x->start(!activated);
    }
}

void GameView::addInventoryItem(int index, TileType::Enum type)
{
    TileLoader & tileLoader = TileLoader::getInstance();
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

void GameView::displayDialog(const QString & text)
{
    GraphicsMenuItem * dialogBox = new GraphicsMenuItem(QSize(100, 40), 2);
    GraphicsText * dialogText = new GraphicsText(text, QSize(100, 40));
    dialogBox->setGraphicsLayoutItem(dialogText);
    dialogBox->setPos(16*5, 16*8);
    dialogBox->setZValue(Layer::GUI_BACKGROUND);
    scene.addItem(dialogBox);
    connect(dialogBox, SIGNAL(itemClickedEvent(const GraphicsMenuItem*)), SLOT(removeDialog(const GraphicsMenuItem*)));
}

void GameView::removeDialog(const GraphicsMenuItem* dialog)
{
    delete dialog;  // Children are deleted by its destructor
}

void GameView::addMenuItem(int index, const QString & text)
{
    auto item = new GraphicsText(text, QSize(40, 10));
    menu->addInventoryItem(index, item);
}

void GameView::displayGameOverMenu()
{
    GraphicsMenuItem * dialogBox = new GraphicsMenuItem(QSize(200, 80), 2);
    GraphicsText * dialogText = new GraphicsText("Game Over - Quit", QSize(200, 80));
    dialogText->setFont(QFont("calibri", 12));
    dialogBox->setGraphicsLayoutItem(dialogText);
    dialogBox->setPos(16*2, 16*6);
    dialogBox->setZValue(Layer::GUI_BACKGROUND);
    scene.addItem(dialogBox);
    connect(dialogBox, SIGNAL(itemClickedEvent(const GraphicsMenuItem*)), SIGNAL(gameOverMenuClickEvent()));
}
