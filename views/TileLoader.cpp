#include "TileLoader.h"

#include "views/AnimatedGraphicsTile.h"
#include "views/PlayerSprite.h"

TileLoader &TileLoader::getInstance()
{
    static TileLoader instance;
    return instance;
}

GraphicsTile * TileLoader::get(const TileType::Enum &tileType) const
{
    AnimatedGraphicsTile * temp;
    switch(tileType) {
    case TileType::PLAYER:  return new PlayerSprite(spriteSheet);

    case TileType::DOOR:    return new AnimatedGraphicsTile(textureSheet, 7, 4, 4);
    case TileType::GATE:    return new AnimatedGraphicsTile(textureSheet, 6, 0, 5);
    case TileType::CHEST:   return new AnimatedGraphicsTile(textureSheet, 7, 8, 6);
    case TileType::SWITCH:  return new AnimatedGraphicsTile(textureSheet, 5, 0, 7);

    case TileType::WALL_N_L:    return new GraphicsTile(textureSheet, 1, 6);
    case TileType::WALL_N_U:    return new GraphicsTile(textureSheet, 0, 6);
    case TileType::WALL_E_U:    return new GraphicsTile(textureSheet, 2, 7);
    case TileType::WALL_S_U:    return new GraphicsTile(textureSheet, 3, 6);
    case TileType::WALL_W_U:    return new GraphicsTile(textureSheet, 2, 5);

    case TileType::WALL_N_PILLAR_L:     return new GraphicsTile(textureSheet, 5, 8);
    case TileType::WALL_N_PILLAR_U:     return new GraphicsTile(textureSheet, 4, 8);
    case TileType::WALL_S_PILLAR_U:     return new GraphicsTile(textureSheet, 5, 7);
    case TileType::WALL_E_PILLAR_U:     return new GraphicsTile(textureSheet, 3, 4);
    case TileType::WALL_E_PILLAR_L:     return new GraphicsTile(textureSheet, 4, 4);
    case TileType::WALL_W_PILLAR_U:     return new GraphicsTile(textureSheet, 3, 3);
    case TileType::WALL_W_PILLAR_L:     return new GraphicsTile(textureSheet, 4, 3);

    case TileType::WALL_NE_CORNER_L:    return new GraphicsTile(textureSheet, 1, 7);
    case TileType::WALL_NE_CORNER_U:    return new GraphicsTile(textureSheet, 0, 7);
    case TileType::WALL_SE_CORNER_U:    return new GraphicsTile(textureSheet, 3, 7);
    case TileType::WALL_SW_CORNER_U:    return new GraphicsTile(textureSheet, 3, 5);
    case TileType::WALL_NW_CORNER_U:    return new GraphicsTile(textureSheet, 0, 5);
    case TileType::WALL_NW_CORNER_L:    return new GraphicsTile(textureSheet, 1, 5);

//    case TileType::WALL_NE_CORNER_INNER_L:
//    case TileType::WALL_NE_CORNER_INNER_U:
//    case TileType::WALL_SE_CORNER_INNER_L:
//    case TileType::WALL_SE_CORNER_INNER_U:
//    case TileType::WALL_SW_CORNER_INNER_U:
//    case TileType::WALL_SW_CORNER_INNER_L:
//    case TileType::WALL_NW_CORNER_INNER_U:
//    case TileType::WALL_NW_CORNER_INNER_L:

    case TileType::PILLAR_L:    return new GraphicsTile(textureSheet, 3, 2);
    case TileType::PILLAR_U:    return new GraphicsTile(textureSheet, 4, 2);

    case TileType::CRATE:       return new GraphicsTile(textureSheet, 7, 14);

    case TileType::ORB_BLUE:    return new GraphicsTile(textureSheet, 6, 19);
    case TileType::ORB_ORANGE:  return new GraphicsTile(textureSheet, 6, 20);
    case TileType::ORB_GREEN:   return new GraphicsTile(textureSheet, 6, 21);
    case TileType::ORB_PINK:    return new GraphicsTile(textureSheet, 6, 22);
    case TileType::ORB_GREY:    return new GraphicsTile(textureSheet, 6, 23);

    case TileType::NPC_BLUE:    return new GraphicsTile(textureSheet, 7, 19);
    case TileType::NPC_ORANGE:  return new GraphicsTile(textureSheet, 7, 20);
    case TileType::NPC_GREEN:   return new GraphicsTile(textureSheet, 7, 21);
    case TileType::NPC_PINK:    return new GraphicsTile(textureSheet, 7, 22);
    case TileType::NPC_GREY:    return new GraphicsTile(textureSheet, 7, 23);

    case TileType::LAMP_BLUE:    temp = new AnimatedGraphicsTile(textureSheet, 6, 8, 4);
                                 temp->setLoopCount(0);
                                 temp->start();
                                 return temp;
    case TileType::LAMP_ORANGE:  temp = new AnimatedGraphicsTile(textureSheet, 6, 13, 3);
                                 temp->setLoopCount(0);
                                 temp->start();
                                 return temp;
    case TileType::LAMP_GREEN:   temp = new AnimatedGraphicsTile(textureSheet, 6, 17, 3);
                                 temp->setLoopCount(0);
                                 temp->start();
                                 return temp;

    case TileType::DOOR_EAST:   return new GraphicsTile(textureSheet, 2, 6);
    case TileType::DOOR_WEST:   return new GraphicsTile(textureSheet, 2, 6);
    case TileType::DOOR_SOUTH:   return new GraphicsTile(textureSheet, 2, 6);

    case TileType::FLOOR:
    default:                    return new GraphicsTile(textureSheet, 2, 6);
    }

}

TileLoader::TileLoader()
{
    textureSheet = QSharedPointer<QPixmap>(new QPixmap(":/sprite_sheets/res/sprite_sheets/dungeon_sheet.png"));
    spriteSheet = QSharedPointer<QPixmap>(new QPixmap(":/sprite_sheets/res/sprite_sheets/knight_16x16_sheet.png"));
}
