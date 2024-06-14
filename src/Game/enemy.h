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
        int Level;
        int x;
        void onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info);
    public:
        Enemy();
        void attachEnemy(Player *player);
        void idle(double deltaTime);
        void shoot();
        void destroy();
        void addEnemy();
        SpaceShipMesh *drawSpaceship(float baseWidth, float baseHeight, float height, int resolution, Vector3 vector3, bool isEnemy);
        int generate_random_number();

    };
}


#endif //GAME_ENGINE_ENEMY_H
