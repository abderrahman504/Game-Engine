#include "Engine.h"
#include "Game/MainGameScene.h"
#include "Game/LightTestScene.cpp"
#include <stdio.h>
#include <GL/freeglut.h>
#include "Game/SoundManager.h"


using namespace Engine;
using namespace Engine::DataTypes;
using namespace Game;

int main(int argc, char** argv)
{
     if (!SoundManager::initialize()) {
        return -1;
    }
    initEngine(argc, argv);
    SceneHead* scene = new Game::MainGameScene();
    setMainScene(scene);
    SoundManager::cleanup();
    return 0;


}
