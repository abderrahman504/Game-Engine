#ifndef COLLISION_INFO_GUARD
#define COLLISION_INFO_GUARD
#include "../DataTypes/Vector3.h"
#include "../Nodes/Node3D/Collider3D.h"

namespace Engine
{
    struct CollisionInfo{
        Nodes::Collider3D *my_collider = nullptr, *other_collider = nullptr;
        DataTypes::Vector3 global_collision_point;
    };
}

#endif