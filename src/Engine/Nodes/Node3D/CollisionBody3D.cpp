#include "CollisionBody3D.h"

namespace Engine
{
namespace Nodes
{
    CollisionBody3D::CollisionBody3D() : Node3D()
    {
        setName("CollisionBody3D");
    }

    void CollisionBody3D::onCollision(CollisionBody3D* other, CollisionInfo info){}
}}