#include "Engine.h"
#include "Game/MainGameScene.h"
#include "Game/LightTestScene.cpp"
#include "Game/UITestScene.cpp"
#include <stdio.h>

using namespace Engine;
using namespace Engine::DataTypes;

int main(int argc, char** argv)
{
    initEngine(argc, argv);
    // SceneHead* scene = new Game::MainGameScene();
    // SceneHead* scene = new LightTestScene();
    SceneHead* scene = new UITestScene();
    
    setMainScene(scene);
    return 0;
}
