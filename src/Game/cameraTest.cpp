#include "../Engine.h"
#include <stdio.h>



namespace Game{
    class CameraTest : public Engine::Nodes::Node3D
    {
        protected:
        void idle(double deltaTime){
            Engine::SceneHead &sceneHead = getSceneHead();
            Vector3 moveDir = Vector3::ZERO;
            if(sceneHead.getInputServer().isKeyPressed('w')) moveDir = moveDir + Vector3::FORWARD;
            if(sceneHead.getInputServer().isKeyPressed('s')) moveDir = moveDir + Vector3::BACK;
            if(sceneHead.getInputServer().isKeyPressed('a')) moveDir = moveDir + Vector3::LEFT;
            if(sceneHead.getInputServer().isKeyPressed('d')) moveDir = moveDir + Vector3::RIGHT;
            if(sceneHead.getInputServer().isKeyPressed(' ')) moveDir = moveDir + Vector3::UP;
            if(sceneHead.getInputServer().isKeyPressed('c')) moveDir = moveDir + Vector3::DOWN;
            if(moveDir.length() != 0)
            {
                moveDir = moveDir.normalize().rotateBy(Orientation());
                float speed = 100;
                Position(Position() + moveDir * speed * deltaTime);
            }
            Vector3 rotateDir = Vector3::ZERO;
            Vector2 mouseDir=sceneHead.getInputServer().getMouseMotion();
            rotateDir.x=mouseDir.x;
            rotateDir.y=mouseDir.y;

//            if(mouseDir) rotateDir = rotateDir + Vector3::UP;
//            if(sceneHead.getInputServer().isKeyPressed('k')) rotateDir = rotateDir + Vector3::DOWN;
//            if(sceneHead.getInputServer().isKeyPressed('j')) rotateDir = rotateDir + Vector3::LEFT;
//            if(sceneHead.getInputServer().isKeyPressed('l')) rotateDir = rotateDir + Vector3::RIGHT;
            if(rotateDir.length() != 0)
            {
                float speed = 10 * PI / 180.0;
                rotateAround(Vector3::DOWN, speed * deltaTime * rotateDir.x);
                rotateAround(Vector3::LEFT, speed * deltaTime * rotateDir.y);

            }

        }
    };
}