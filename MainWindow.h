#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GameController.h"
#include "GameModel.h"
#include "GameView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent(QResizeEvent *);

public slots:


private:
    GameController * gameController;
    GameModel * gameModel;
    GameView * gameView;

};

#endif // MAINWINDOW_H
