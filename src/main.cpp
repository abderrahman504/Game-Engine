#include "Engine.h"
#include "Game/MainGameScene.h"
#include "Game/LightTestScene.cpp"
#include <stdio.h>
#include <GL/freeglut.h>

using namespace Engine;
using namespace Engine::DataTypes;

int main(int argc, char** argv)
{
    initEngine(argc, argv);
    SceneHead* scene = new Game::MainGameScene();
    setMainScene(scene);

    return 0;
}

