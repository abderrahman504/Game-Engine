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
                float speed = 300;
                Position(Position() + moveDir * speed * deltaTime);
            }
            Vector2 mouseDir = inputServer.getMouseMotion();

            if(mouseDir.length() != 0)
            {
                float speed = 10 * PI / 180.0;
                float xAngle =  speed * deltaTime * -1*mouseDir.x;
                float yAngle = speed * deltaTime * mouseDir.y;

                // Vector3 pitchVec = getForward();
                // Vector3 zeroPitchVec = Vector3(pitchVec.x,0,pitchVec.z);
                rotateAround(Vector3::UP, xAngle);
                rotateAround(getUp().cross(getForward()), yAngle);
                Vector3 direction = getForward();
                lookTowards(getForward(), Vector3::UP);

            }

        }
    };
}