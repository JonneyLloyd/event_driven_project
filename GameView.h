#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "DirectionEnum.h"

// temp
#include "views/GraphicsTile.h"
#include "views/AnimatedGraphicsTile.h"
#include "views/PlayerSprite.h"

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

private:
    PlayerSprite * player;

    // temp
    GraphicsTile * testTile;
    GraphicsTile * testAnimatedTile;
    GraphicsTile * testAnimatedTile2;
    GraphicsTile * testAnimatedTile3;


protected:
    void keyPressEvent(QKeyEvent *event);   // Overrides parent

signals:
    void moveEvent(Direction direction);    // Notifies controller of a move

public slots:
    void movePlayer(Direction direction);   // Listens for controller
                                            // Moves the player on the screen

};

#endif // GAMEVIEW_H
