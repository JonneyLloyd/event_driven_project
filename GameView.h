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
    QHash<std::pair<int, int>, GraphicsTile *> * interactables;

    void initScene();
    void initPlayer();
    void initInventory();
    void initMenu();

protected:
    void keyPressEvent(QKeyEvent *event);   // Overrides parent

signals:
    void moveEvent(Direction::Enum direction);    // Notifies controller of a move
    void inventoryClickEvent(int index);

    void interactEvent();
    void menuClickEvent(int index);
    void gameOverMenuClickEvent();
    void pauseClickEvent();

public slots:
    void movePlayer(Direction::Enum direction);   // Listens for controller
                                                  // Moves the player on the screen
    void displayFloor(QHash<std::pair<int, int>, Tile *> * floor,
                      QHash<std::pair<int, int>, Tile *> * walls,
                      QHash<std::pair<int, int>, Tile *> * doors);
    void setInteractableItemState(const std::pair<int, int> & position, bool activated, int loopCount);

    void addInventoryItem(int index, TileType::Enum type);
    void removeInventoryItem(int index);
    void setPlayerLocation(int x, int y);
    void setPlayerHeading(Direction::Enum direction);
    void displayMenu(bool visible);
    void displayDialog(const QString &text);
    void addMenuItem(int index, const QString &text);
    void displayGameOverMenu();

private slots:
    void removeDialog(const GraphicsMenuItem *dialog);

};

#endif // GAMEVIEW_H
