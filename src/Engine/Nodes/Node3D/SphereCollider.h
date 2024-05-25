#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H
#include "Collider3D.h"


namespace Engine::Nodes{
    class SphereCollider : public Collider3D
    {
        public:
        float radius = 1;

        SphereCollider();
        SphereCollider(float radius);
    };
}

#endif