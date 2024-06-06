#ifndef COLLISION_BODY_3D_GUARD
#define COLLISION_BODY_3D_GUARD
#include "Node3D.h"
#include "../../Physics/CollisionInfo.h"

namespace Engine
{
namespace Nodes
{
    class CollisionBody3D : public Node3D
    {
        public:
        unsigned short collisionLayer = 0;
        unsigned short collisionMask = 0;
        bool disabled = false;

        CollisionBody3D();
        virtual void onCollision(CollisionBody3D* other, CollisionInfo info);
    };
}}


#endif