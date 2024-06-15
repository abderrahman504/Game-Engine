
#ifndef GAME_ENGINE_PICKABLE_H
#define GAME_ENGINE_PICKABLE_H

#include "../Engine.h"
#include <stdio.h>
#include "MainPlayer.h"
#include "SoundManager.h"
#include "Bullet.h"

namespace Game
{
    class Pickable : public Engine::Nodes::CollisionBody3D
    {
        // make vector of Bullets
    private:
        float lifeTime;
        float maxLifeTime;
        float radius;
        int resolution;
        float health = 10;
        int type;
        SphereMesh *mesh;
    protected:
        void idle(double deltaTime);
        void onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info);
    public:
        Pickable(Vector3 position,char * path,float radius, int resolution, float maxLifeTime, float damage, int type);
        void destroy();
    };

}

#endif // GAME_ENGINE_PICKABLE_H
