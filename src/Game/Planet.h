#ifndef PLANET_GUARD
#define PLANET_GUARD
#include "../Engine/Nodes.h"
#include "../Engine/DataTypes.h"

using namespace Engine::Nodes;

namespace Game{
    class Planet : public SphereMesh
    {
        public:
        float orbitRadius = 1;
        float orbitSpeed = PI * 0.05;
        float orbitAngle = 0;

        Planet(float radius, int resolution);
        void idle(double deltaTime);
    };
}

#endif