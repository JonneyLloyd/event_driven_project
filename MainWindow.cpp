#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gameModel.setParent(this);
    gameView.setParent(this);
    gameController = new GameController(&gameModel, &gameView, this);
    this->setWindowTitle(QString("Don't Take The Rabbit"));
    this->setCentralWidget(&gameView);

//    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
//    this->showFullScreen();
//    this->showMaximized();

}

MainWindow::~MainWindow()
{
    delete gameController;
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    QRectF bounds = gameView.scene.sceneRect();
    // Set margins
    bounds.setWidth(bounds.width()*1.2);
    bounds.setHeight(bounds.height()*1.2);
    gameView.fitInView(bounds, Qt::KeepAspectRatio);
}
