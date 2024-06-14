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
        Player *player;
        double shootingInterval;
        double timeSinceLastShot;
        void onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info);
    public:
        Enemy();
        void attachEnemy(Player *player);
        void idle(double deltaTime);
        void shoot();
        void destroy();

    };
}


#endif //GAME_ENGINE_ENEMY_H
