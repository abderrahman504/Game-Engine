#ifndef COLLISION_INFO_GUARD
#define COLLISION_INFO_GUARD
#include "Vector3.h"


namespace Engine
{
    class Collider3D;
    struct CollisionInfo{
        Collider3D *my_collider = nullptr, *other_collider = nullptr;
        DataTypes::Vector3 global_collision_point;
    };
}

#endif