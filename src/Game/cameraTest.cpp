#include "../Engine.h"
#include <stdio.h>



namespace Game{
    class CameraTest : public Engine::Nodes::Node3D
    {
        protected:
        void idle(double deltaTime){
            Engine::InputServer &inputServer = getSceneHead().getInputServer();
            Vector3 moveDir = Vector3::ZERO;
            if(inputServer.isKeyPressed('w')) moveDir = moveDir + Vector3::FORWARD;
            if(inputServer.isKeyPressed('s')) moveDir = moveDir + Vector3::BACK;
            if(inputServer.isKeyPressed('a')) moveDir = moveDir + Vector3::LEFT;
            if(inputServer.isKeyPressed('d')) moveDir = moveDir + Vector3::RIGHT;
            if(inputServer.isKeyPressed(' ')) moveDir = moveDir + Vector3::UP;
            if(inputServer.isKeyPressed('c')) moveDir = moveDir + Vector3::DOWN;
            if(moveDir.length() != 0)
            {
                moveDir = moveDir.normalize().rotateBy(Orientation());
                float speed = 100;
                Position(Position() + moveDir * speed * deltaTime);
            }
            Vector2 mouseDir = inputServer.getMouseMotion();

//            if(mouseDir) rotateDir = rotateDir + Vector3::UP;
//            if(sceneHead.getInputServer().isKeyPressed('k')) rotateDir = rotateDir + Vector3::DOWN;
//            if(sceneHead.getInputServer().isKeyPressed('j')) rotateDir = rotateDir + Vector3::LEFT;
//            if(sceneHead.getInputServer().isKeyPressed('l')) rotateDir = rotateDir + Vector3::RIGHT;
            if(mouseDir.length() != 0)
            {
                float speed = 10 * PI / 180.0;
                rotateAround(Vector3::DOWN, speed * deltaTime * mouseDir.x);
                rotateAround(Vector3::LEFT, speed * deltaTime * mouseDir.y);

            }

        }
    };
}