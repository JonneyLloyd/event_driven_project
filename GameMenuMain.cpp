#include "gamemenumain.h"
#include <QGraphicsScene>
#include <QImage>
#include <QLabel>

GameMenuMain::GameMenuMain(QObject *parent) : QGraphicsScene(parent)
{
    // Create Rectangle
    rect = new QGraphicsRectItem();
    rect->setRect(20, 50, 100, 100);
    this->addItem(rect);

    btn = new QPushButton(QString("Test"));
    this->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), SIGNAL(actionStart()));

    QImage sprite_sheet(":/sprite_sheets/res/sprite_sheets/dungeon_sheet.png");
    QImage sprite = sprite_sheet.copy(0, 0, 32, 32);
    QGraphicsPixmapItem * myLabel = new QGraphicsPixmapItem(QPixmap::fromImage(sprite));
    myLabel->setPos(200, 200);
    this->addItem(myLabel);

    // Second image causes crash?
//    QGraphicsPixmapItem * myLabel2 = new QGraphicsPixmapItem(QPixmap::fromImage(sprite));
//    myLabel2->setPos(200, 300);
//    this->addItem(myLabel2);

// Uncommenting this shows that there is a memory management problem somewhere
//    this->removeItem(myLabel);
//    this->removeItem(myLabel2);
//    delete myLabel;
//    delete myLabel2;
}

GameMenuMain::~GameMenuMain()
{

}

