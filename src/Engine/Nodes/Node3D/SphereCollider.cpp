#include "SphereCollider.h"

namespace Engine::Nodes{

    SphereCollider::SphereCollider() : Collider3D(){
        setName("SphereCollider");
    }
    SphereCollider::SphereCollider(float radius) : Collider3D()
    {
        this->radius = radius;
        this->setName("SphereCollider");
    }
}
