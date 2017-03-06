#include "GameModel.h"

#include <QDebug>

GameModel::GameModel(QObject *parent) : QObject(parent)
{

}

void GameModel::move(Direction direction)
{
    qDebug() << "GameModel: Valid move";
    emit movePlayerEvent(direction);
}
