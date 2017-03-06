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
     *
     * param mainWindow   The main window to add content to
     */
    explicit GameController(GameModel *gameModel, GameView *gameView, QObject *parent = 0);

private:
    GameModel * gameModel;
    GameView * gameView;

signals:


public slots:


};

#endif // GAMECONTROLLER_H
