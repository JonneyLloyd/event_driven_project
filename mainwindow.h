#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    // Splash, into dialog, game over, high score
    void displayMenu();
    void displayGame();

private:
//    Ui::Game *ui;
    QGraphicsScene * scene;
    QGraphicsView * view;
};

#endif // MAINWINDOW_H
