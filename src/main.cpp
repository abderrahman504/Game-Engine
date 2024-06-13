#include "Engine.h"
#include "Game/MainGameScene.h"
#include "Game/CollisionTestScene.cpp"
#include <stdio.h>

using namespace Engine;
using namespace Engine::DataTypes;

int main(int argc, char** argv)
{
    initEngine(argc, argv);
    SceneHead* scene = new Game::MainGameScene();
    // SceneHead* scene = new CollisionTestScene();
    setMainScene(scene);
    return 0;
}
