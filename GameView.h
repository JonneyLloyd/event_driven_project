#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "DirectionEnum.h"
#include "PlayerSprite.h"

/*
 * GameView handles visuals and interacts with widgets/items.
 * Following MVC it is controlled externally.
 * User interaction is transmitted to the controller via signals.
 */
class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    /*
     * Constructor
     *
     * param view   The view to add the scene to
     */
    explicit GameView(QWidget *parent = 0);

private:
    QGraphicsScene scene;   // Opted to contain the scene rather than inherit
                            // from it as the other attributes/items will be
                            // added to it. It would be odd to add something
                            // to something it is already in.
    PlayerSprite * player;


protected:
    void keyPressEvent(QKeyEvent *event);   // Overrides parent

signals:
    void moveEvent(Direction direction);    // Notifies controller of a move

public slots:
    void movePlayer(Direction direction);   // Listens for controller
                                            // Moves the player on the screen

};

#endif // GAMEVIEW_H
