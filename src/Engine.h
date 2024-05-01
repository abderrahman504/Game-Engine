#ifndef ENGINE_GUARD
#define ENGINE_GUARD
#include "Engine/SceneHead.h"
#include "Engine/InputServer.h"
#include "Engine/PhysicsServer.h"
#include "Engine/DataTypes.h"
#include "Engine/Nodes.h"



namespace Engine{

    void initEngine(int argc, char** argv);
    void setMainScene(Engine::SceneHead* scene);

}


#endif