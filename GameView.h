#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "DirectionEnum.h"
#include "views/GraphicsTile.h"
#include "views/AnimatedGraphicsTile.h"
#include "views/PlayerSprite.h"
#include "views/GraphicsMenu.h"
#include "models/Tile.h"

/*
 * GameView handles visuals and interacts with widgets/items.
 * Following MVC it is controlled externally.
 * User interaction is transmitted to the controller via signals.
 */
class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    QGraphicsScene scene;

    /*
     * Constructor
     *
     * param view   The view to add the scene to
     */
    explicit GameView(QWidget *parent = 0);
    ~GameView();

private:
    PlayerSprite * player;
    GraphicsMenu * inventory;
    GraphicsMenu * menu;

    void initScene();
    void initPlayer();
    void initInventory();
    void initMenu();

    QHash<std::pair<int, int>, GraphicsTile *> * interactables;


    // temp
    GraphicsTile * testTile;
    GraphicsTile * testAnimatedTile;
    GraphicsTile * testAnimatedTile2;
    GraphicsTile * testAnimatedTile3;
    void testInitAnimation();
    void testAnimation();


protected:
    void keyPressEvent(QKeyEvent *event);   // Overrides parent

signals:
    void moveEvent(Direction::Enum direction);    // Notifies controller of a move
    void inventoryClickEvent(int index);

    void interactEvent();
    void menuClickEvent(int index);
    void pauseClickEvent();

public slots:
    void movePlayer(Direction::Enum direction);   // Listens for controller
                                            // Moves the player on the screen
    void displayFloor(QHash<std::pair<int, int>, Tile *> * floor,
                      QHash<std::pair<int, int>, Tile *> * walls,
                      QHash<std::pair<int, int>, Tile *> * doors);
    void removeInteractableItem(const std::pair<int, int> & position); // TODO
    void setInteractableItemState(const std::pair<int, int> & position, bool activated, int loopCount); // TODO

    void addInventoryItem(int index, TileType::Enum type);
    void removeInventoryItem(int index);
    void setPlayerLocation(int x, int y);
    void setPlayerHeading(Direction::Enum direction);
    void displayMenu(bool visible);
    void displayDialog(QString text);
    void addMenuItem(int index, QString text);

private slots:
    void removeDialog(GraphicsMenuItem *dialog);

};

#endif // GAMEVIEW_H
