#ifndef MAIN_GAME_SCENE_H
#define MAIN_GAME_SCENE_H

#include "../Engine.h"

namespace Game {
    class MainGameScene : public Engine::SceneHead {
    public:
        Engine::Nodes::Node *constructTree();
    };
}


#endif