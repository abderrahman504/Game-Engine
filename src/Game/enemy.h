//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_ENEMY_H
#define GAME_ENGINE_ENEMY_H

#include "../Engine.h"
#include <stdio.h>

#include "player.h"


namespace Game {

    class Enemy : public Player {
    SpaceShipMesh* player;
    public:
        Enemy();
        void move();
        void attachEnemy(SpaceShipMesh* player);
        void idle(double deltaTime);
    };
}


#endif //GAME_ENGINE_ENEMY_H
