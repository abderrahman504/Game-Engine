//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_BULLET_H
#define GAME_ENGINE_BULLET_H

#include "../Engine.h"
#include <stdio.h>


namespace Game {
    class Bullet: public Engine::Nodes::CollisionBody3D {
        float speed;
        float lifeTime;
        float maxLifeTime;
        float radius;
        float height;
        float damage = 10;
        CylinderMesh* mesh;
        protected:
        void idle(double deltaTime);
        public:
        Vector3 moveDir;
        Bullet(float radius, float height, int resolution, float speed,float maxLifeTime,float damage);
        void destroy();
        float getDamage();
    };
}



#endif //GAME_ENGINE_BULLET_H
