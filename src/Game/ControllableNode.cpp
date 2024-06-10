#include "../Engine.h"

using namespace Engine;
using namespace Engine::Nodes;
using namespace Engine::DataTypes;

class ControllableNode : public Node3D
{
    public:
    int forward = 'w', back = 's', left = 'a', right = 'd', up = ' ', down = 'c';


    protected:
    void idle(double deltaTime)
    {
        InputServer &inputServer = getSceneHead().getInputServer();
        Vector3 moveDir = Vector3::ZERO;
        if(inputServer.isKeyPressed(forward)) moveDir = moveDir + Vector3::FORWARD;
        if(inputServer.isKeyPressed(back)) moveDir = moveDir + Vector3::BACK;
        if(inputServer.isKeyPressed(left)) moveDir = moveDir + Vector3::LEFT;
        if(inputServer.isKeyPressed(right)) moveDir = moveDir + Vector3::RIGHT;
        if(inputServer.isKeyPressed(up)) moveDir = moveDir + Vector3::UP;
        if(inputServer.isKeyPressed(down)) moveDir = moveDir + Vector3::DOWN;
        if(moveDir.length() != 0)
        {
            moveDir = moveDir.normalize().rotateBy(orientation);
            float speed = 70;
            position = position + moveDir * speed * deltaTime;
        }
    }
};