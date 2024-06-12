//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_BULLET_H
#define GAME_ENGINE_BULLET_H

#include "../Engine.h"
#include <stdio.h>


namespace Game {
    class bullet: public Engine::Nodes::CollisionBody3D , public Engine::Nodes::CylinderMesh{

        float speed;
        float maxSpeed;
        float acceleration;
        float maxAcceleration;
        float lifeTime;
        float maxLifeTime;
        float damage;
        float radius;

        public:
        bullet(float radius, float height, int resolution, float speed, float maxSpeed, float acceleration, float maxAcceleration, float lifeTime, float maxLifeTime, float damage);



    };
}



#endif //GAME_ENGINE_BULLET_H
