#include "GameView.h"
#include "Button.h"
#include "views/TileLoader.h"
#include "TileTypeEnum.h"
#include <QDebug>

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



    TileLoader tileLoader = TileLoader::getInstance();

    QPixmap * textureSheet = new QPixmap(":/sprite_sheets/res/sprite_sheets/dungeon_sheet.png");


    // Example of loading a basic tile (since behaviour of e.g. floor and walls never changes they can use the same class)
    testTile = new GraphicsTile(textureSheet, 7, 8);
    scene.addItem(testTile);
    testTile->setPos(16*2, 16*2);

    GraphicsTile * wall = new GraphicsTile(textureSheet, 0, 5);
    scene.addItem(wall);
    wall->setPos(16*10, 16*10);



    player = new PlayerSprite(new QPixmap(":/sprite_sheets/res/sprite_sheets/knight_16x16_sheet.png"));
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
    //  Figure out if QGraphicsItem * parent is needed/wanted and adjust tile objects (since it is the last param)

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
    /*
     * Code checks next tile before movement
     * Will not move to intraversable tiles
     * WARNING if for some reason the next tile over is empty/void this will cause crash
    */
    qDebug() << "GameView: Player is moving";
    player->move(direction);

    // temp
    static int n = 0;
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile)->start(n%2 == 0 ? false:true);
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile2)->start(n%2 == 0 ? false:true);
    static_cast<AnimatedGraphicsTile*>(testAnimatedTile3)->start(n%2 == 0 ? false:true);
    n++;
}

//TODO signal to generate room graphics
//seems to be connected but never enters the function after the emit from model
void GameView::displayFloor(QHash<std::pair<int, int>, Tile *> * floor)
{
    qDebug() << "SIGNAL RECEIVED";

    TileLoader tileLoader = TileLoader::getInstance();
    GraphicsTile * tile;
    QHash<std::pair<int, int>, Tile*>::iterator i;
    for (i = floor->begin(); i != floor->end(); ++i){
        if(i.value()->getId()==9){
            tile = tileLoader.get(TileType::FLOOR);
            scene.addItem(tile);
            tile->setPos(16*i.key().first, 16*i.key().second);
        }

    }
/*
    QHash<std::pair<int, int>, Tile*> * layer2 = test->generateRoom();
    GraphicsTile * tile;
    for (i = layer2->begin(); i != layer2->end(); ++i){
        if(i.value()->getId()==5){ //west wall
                    tile = tileLoader.get(TileType::WALL_W_U);
        }

        else if(i.value()->getId()==6){ //east wall
            tile = tileLoader.get(TileType::WALL_E_U);
        }

        else if(i.value()->getId()==7){ //north wall
            tile = tileLoader.get(TileType::WALL_N_L);
        }

        else if(i.value()->getId()==8){ //south wall
            tile = tileLoader.get(TileType::WALL_S_U);
        }

        else if(i.value()->getId()==1){ //northwest corner
            tile = tileLoader.get(TileType::WALL_NW_CORNER_L);
        }

        else if(i.value()->getId()==2){ //northeast corner
            tile = tileLoader.get(TileType::WALL_NE_CORNER_L);
        }

        else if(i.value()->getId()==3){ //southwest corner
            tile = tileLoader.get(TileType::WALL_SW_CORNER_U);
        }

        else if(i.value()->getId()==4){ //southeast corner
            tile = tileLoader.get(TileType::WALL_SE_CORNER_U);
        }
        tile->setTraversable(i.value()->getTraversable());
        scene.addItem(tile);
        tile->setPos(16*i.key().first, 16*i.key().second);
    }*/

}
