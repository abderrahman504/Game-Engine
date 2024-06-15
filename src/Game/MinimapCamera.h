#ifndef MINIMAP_CAMERA_H
#define MINIMAP_CAMERA_H

#include "../Engine.h"

using namespace Engine::Nodes;
using namespace Engine::DataTypes;
using namespace Engine;

class MinimapCamera : public Camera3D {

    public:

    Node3D* target;
    float distance_from_target = 700;

    void idle(double deltaTime)
    {
        if(target != nullptr)
        {
            Vector3 targetPosition = target->position;
            Vector3 cameraPosition = targetPosition + Vector3(0, distance_from_target, 0);
            this->position = cameraPosition;
            this->lookTowards(Vector3::DOWN, Vector3::FORWARD);
        }
    }


};


#endif