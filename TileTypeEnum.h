#ifndef TILETYPE_H
#define TILETYPE_H

enum TileType { PLAYER, DOOR, CHEST, SWITCH,
                WALL_N_L,
                WALL_N_U,
                WALL_E_U,
                WALL_S_U,
                WALL_W_U,

                WALL_N_PILLAR_L,
                WALL_N_PILLAR_U,
                WALL_S_PILLAR_U,
                WALL_E_PILLAR_U,
                WALL_E_PILLAR_L,
                WALL_W_PILLAR_U,
                WALL_W_PILLAR_L,

                WALL_NE_CORNER_L,
                WALL_NE_CORNER_U,
                WALL_SE_CORNER_U,
                WALL_SW_CORNER_U,
                WALL_NW_CORNER_U,
                WALL_NW_CORNER_L,

//                WALL_NE_CORNER_INNER_L,
//                WALL_NE_CORNER_INNER_U,
//                WALL_SE_CORNER_INNER_L,
//                WALL_SE_CORNER_INNER_U,
//                WALL_SW_CORNER_INNER_U,
//                WALL_SW_CORNER_INNER_L,
//                WALL_NW_CORNER_INNER_U,
//                WALL_NW_CORNER_INNER_L,

                PILLAR_L, PILLAR_U,
                CRATE,
                ORB_BLUE, ORB_ORANGE, ORB_GREEN, ORB_PINK, ORB_GREY
              };

#endif // TILETYPE_H
