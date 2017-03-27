#-------------------------------------------------
#
# Project created by QtCreator 2017-02-15T17:33:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DontTakeTheRabbit
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    MainWindow.cpp \
    Button.cpp \
    GameModel.cpp \
    GameController.cpp \
    GameView.cpp \
    views/TileLoader.cpp \
    views/GraphicsTile.cpp \
    views/AnimatedGraphicsTile.cpp \
    models/GenerateRoom.cpp \
    models/Player.cpp \
    models/Tile.cpp \
    models/InteractableTile.cpp \
    views/PlayerSprite.cpp \
    views/GraphicsInventory.cpp \
    views/GraphicsInventoryItem.cpp \
    models/State.cpp

HEADERS  += \
    Button.h \
    GameModel.h \
    GameController.h \
    GameView.h \
    DirectionEnum.h \
    MainWindow.h \
    views/TileLoader.h \
    TileTypeEnum.h \
    views/GraphicsTile.h \
    views/AnimatedGraphicsTile.h \
    models/GenerateRoom.h \
    models/Player.h \
    models/Tile.h \
    models/Interactable.h \
    models/InteractableTile.h \
    views/PlayerSprite.h \
    views/GraphicsInventory.h \
    views/GraphicsInventoryItem.h \
    models/State.h

FORMS    +=

RESOURCES += \
    resources.qrc
