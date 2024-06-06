#ifndef PHYSICS_SERVER_GUARD
#define PHYSICS_SERVER_GUARD
#include "Nodes/Node.h"


namespace Engine{
    class SceneHead;

    

    class PhysicsServer
    {
        friend class SceneHead;
        
        void update(double delta, Nodes::Node* root);
    };
}


#endif