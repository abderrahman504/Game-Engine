#include "../Engine.h"
#include <stdio.h>

using namespace Engine;
using namespace Engine::Nodes;

class ControllableBody : public CollisionBody3D
{
    protected:
    void physics(double deltaTime)
    {
        float speed = 100;
        InputServer& input = getSceneHead().getInputServer();
        Vector3 moveDir = Vector3::ZERO;
        if(input.isKeyPressed('w')) moveDir = moveDir + Vector3::FORWARD;
        if(input.isKeyPressed('s')) moveDir = moveDir + Vector3::BACK;
        if(input.isKeyPressed('a')) moveDir = moveDir + Vector3::LEFT;
        if(input.isKeyPressed('d')) moveDir = moveDir + Vector3::RIGHT;
        if(input.isKeyPressed(' ')) moveDir = moveDir + Vector3::UP;
        if(input.isKeyPressed('c')) moveDir = moveDir + Vector3::DOWN;
        
        moveDir.normalize();
        position = position + moveDir * speed * deltaTime;
    }

    public:
    void onCollision(CollisionBody3D* other, CollisionInfo info)
    {
        printf("Collided at (%f, %f, %f)\n", info.global_collision_point.x, info.global_collision_point.y, info.global_collision_point.z);
    }
};
