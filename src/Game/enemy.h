//
// Created by AhmedSamir on 12/06/2024.
//
#ifndef GAME_ENGINE_ENEMY_H
#define GAME_ENGINE_ENEMY_H

#include "../Engine.h"
#include "player.h"
#include <stdio.h>

namespace Game {
    class Enemy : public CollisionBody3D {
    public:
        Player *player = nullptr;
        double shootingInterval = 3;
        double timeSinceLastShot = 3;
        int health = 100;
        int Level;
        int x;
        Vector3 velocity = Vector3::ZERO;
        float max_speed = 50;
        float acceleration = 30;

        float rotation_speed = 0;
        float max_rotation_speed = 90 * PI / 180.0;
        float rotation_acceleration = 30 * PI / 180.0;

        float min_distance_to_player = 200;

        void onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info);

        Enemy();

        void attachEnemy(Player *player);

        void idle(double deltaTime);

        void shoot();

        void destroy();

        void addEnemy();

        SpaceShipMesh *
        drawSpaceship(float baseWidth, float baseHeight, float height, int resolution, Vector3 vector3, bool isEnemy);

        int generate_random_number();


    };
}




#endif
