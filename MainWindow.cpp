#include "mainwindow.h"
#include "ui_game.h"
#include "gamemenumain.h"
#include "gamescene.h"
#include <QGraphicsRectItem>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    scene(new GameScene(this)),
    view(new QGraphicsView(scene, this))
//    , ui(new Ui::Game)
{
//    ui->setupUi(this);

    // Add to the window
    this->setCentralWidget(view);
    this->setWindowTitle(QString("Don't Take The Rabbit"));

    // View
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800, 600);

//    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
//    showFullScreen();
//    showMaximized();

    displayGame();

}

MainWindow::~MainWindow()
{
    //    delete ui;
}


// Not sure if below is the best way to be swapping
// Should I swap scenes for each menu or should I just keep one scene and manage the contents
void MainWindow::displayMenu()
{
//    delete scene;  // didn't work, crash probably because view had dangling pointer, but I need to delete before I reassign scene?
                            // Investigate better way for memory management
    scene->clear();         // Better? delete contents (will this delete objects added with pointers too?)
    scene->deleteLater();   //         delete the object itself later? (should I create a destructor to delete pointers?)
    scene = new GameMenuMain(this);
    scene->setSceneRect(0, 0, 800, 600);  // Origin of the view
    view->setScene(scene);
    connect(scene, SIGNAL(actionStart()), this, SLOT(displayGame()));
}

void MainWindow::displayGame()
{
    scene->clear();
    scene->deleteLater();
    scene = new GameScene(this);
    scene->setSceneRect(0, 0, 800, 600);  // Origin of the view
    view->setScene(scene);
    connect(scene, SIGNAL(actionQuit()), this, SLOT(displayMenu()));
}
