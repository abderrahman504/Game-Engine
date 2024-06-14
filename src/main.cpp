#include "Engine.h"
#include "Game/MainGameScene.h"
#include "Game/LightTestScene.cpp"
#include "Game/UITestScene.cpp"
#include "Game/SoundManager.h"
#include <stdio.h>
#include <GL/freeglut.h>


#ifdef _WIN32
#include <windows.h>
#endif


using namespace Engine;
using namespace Engine::DataTypes;
using namespace Game;

int main(int argc, char* argv[])
{
    if (!SoundManager::initialize()) {
        return -1;
    }

    initEngine(argc, argv);
    SceneHead* scene = new Game::MainGameScene();
    // SceneHead* scene = new Game::MainGameScene();
    // SceneHead* scene = new LightTestScene();
    // SceneHead* scene = new UITestScene();
    
    setMainScene(scene);
    SoundManager::cleanup();
    return 0;
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    if (!SoundManager::initialize()) {
        return -1;
    }
    int argc = 0;
    char* argv[1] = {(char*) lpCmdLine};
    
    main(argc, argv);
    return 0;
}

#endif