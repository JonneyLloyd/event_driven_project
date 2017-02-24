#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>

#include "DirectionEnum.h"

/*
 * GameModel handles state and logic of the game.
 * Following MVC it is controlled externally.
 * State changes are transmitted to the controller via signals.
 *
 * Possibly create a game loop here using a timer asynchronously and emitting signals
 * if the state changes
 */
class GameModel : public QObject
{
    Q_OBJECT

public:
    explicit GameModel(QObject *parent = 0);

signals:
    void movePlayerEvent(Direction Direction);  // Notifies controller to move player
                                                // Should this be direction or position with animation=true default flag

public slots:
    void move(Direction Direction);     // Listens for controller
                                        // Moves the player in game state

};

#endif // GAMEMODEL_H
