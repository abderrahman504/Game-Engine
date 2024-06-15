#ifndef PLAYER_CAMERA_PIVOT_H
#define PLAYER_CAMERA_PIVOT_H

#include "../Engine.h"
#include "MainPlayer.h"

using namespace Engine;
using namespace Engine::Nodes;
using namespace Engine::DataTypes;


class PlayerCameraPivot : public Engine::Nodes::Node3D {

    public:
    Game::MainPlayer* player;

    void idle(double deltaTime) {
        InputServer& inputServer = getSceneHead().getInputServer();
        Vector2 mouseDir = inputServer.getMouseMotion();

        if (mouseDir.length() != 0) {
            float speed = 10 * PI / 180.0;
            float xAngle = speed * deltaTime * -1 * mouseDir.x;
            float yAngle = speed * deltaTime * mouseDir.y;

            rotateAround(Vector3::UP, xAngle);
            Vector3 right = getUp().cross(getForward());
            rotateAround(right, yAngle);
            if (getForward().dot(Vector3::UP) == 0)
                rotateAround(right, -0.01);
            lookTowards(getForward(), Vector3::UP);
        }
        if(player != nullptr)
        {
            position = player->position;
            player->look_direction = getForward();
        }
    }

};

#endif