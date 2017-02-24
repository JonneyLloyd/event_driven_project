#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      gameController(*this)
{
    this->setWindowTitle(QString("Don't Take The Rabbit"));

}

MainWindow::~MainWindow()
{

}
