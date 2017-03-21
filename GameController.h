#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>

#include "GameModel.h"
#include "GameView.h"

/*
 * GameController handels communication between the model and view
 * via signals and slots.
 */
class GameController : public QObject
{
    Q_OBJECT

public:
    /*
     * Constructor
     */
    explicit GameController(GameModel *gameModel, GameView *gameView, QObject *parent = 0);

private:
    GameModel * gameModel;
    GameView * gameView;

signals:
    void generateNewRoom();

public slots:


};

#endif // GAMECONTROLLER_H
