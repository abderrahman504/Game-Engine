//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_BULLET_H
#define GAME_ENGINE_BULLET_H

#include "../Engine.h"
#include <stdio.h>

#include "SoundManager.h"

enum BulletType{
    BULLET,
    LASER,
    MISSILE
};

struct BulletData{
    char* txtPath;
    char* soundPath;
    float damage;
    BulletType type;
};

const BulletData BULLETS_DATA[] = {
        {"../resources/images/bullet1.jpeg","../resources/sounds/gun.mp3",10,BULLET},
        {"../resources/images/bullet2.jpeg","../resources/sounds/laser.mp3",20,LASER},
        {"../resources/images/bullet3.jpeg","../resources/sounds/peow.mp3",30,MISSILE}
};

namespace Game {
    class Bullet: public Engine::Nodes::CollisionBody3D {
        float speed;
        float lifeTime;
        float maxLifeTime;
        float radius;
        float height;
        float damage = 10;
        int type;
        SphereMesh* mesh;
        protected:
        void idle(double deltaTime);
        public:
        bool shooter;
        Vector3 moveDir;
        Bullet(float radius, int resolution, float speed,float maxLifeTime,float damage,int type,bool sound);
        void destroy();
        float getDamage();
    };
}



#endif //GAME_ENGINE_BULLET_H
