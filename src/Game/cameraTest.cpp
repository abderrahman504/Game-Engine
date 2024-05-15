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
                // printf("Position = (%f, %f, %f)\n", Position().x, Position().y, Position().z);
            }
            //Rotation input
            Vector2 rotateDir = inputServer.getMouseMotion();
            if(rotateDir.length() != 0)
            {
                Vector3 forward = getForward();
                // printf("forward before = (%.2lf, %.2lf, %.2lf), ", forward.x, forward.y, forward.z);
                float speed = 70 * PI / 180.0;
                float anglex = speed * deltaTime * rotateDir.x;
                float angley = speed * deltaTime * rotateDir.y;

                //Limit the forward vector to prevent flipping
                float angleLimit = 10 * PI / 180.0;
                float currentAngleWithUp = forward.angle_to(Vector3::UP);
                float currentAngleWithDown = forward.angle_to(Vector3::DOWN);
                if(currentAngleWithUp - angley < angleLimit)
                    angley = currentAngleWithUp - angleLimit;
                if(currentAngleWithDown + angley < angleLimit)
                    angley = -1 * (currentAngleWithDown - angleLimit);

                rotateAround(Vector3::DOWN, anglex);
                rotateAround(Vector3::LEFT, angley);
                lookTowards(getForward(), Vector3::UP);
            }

        }
    };
}