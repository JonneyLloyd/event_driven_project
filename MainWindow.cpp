#include "MainWindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gameModel = new GameModel;
    gameView = new GameView;
    gameController = new GameController(gameModel, gameView);
    this->setWindowTitle(QString("Don't Take The Rabbit"));
    this->setCentralWidget(gameView);

//    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
//    this->showFullScreen();
//    this->showMaximized();

}

MainWindow::~MainWindow()
{

}

void MainWindow::resizeEvent(QResizeEvent *)
{
    QRectF bounds = gameView->scene.sceneRect();
    // Implement a maximum size to stop scaling
    bounds.setWidth(bounds.width()*1.2);
    bounds.setHeight(bounds.height()*1.2);
    gameView->fitInView(bounds, Qt::KeepAspectRatio);
}
