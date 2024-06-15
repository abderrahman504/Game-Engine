//
// Created by mado on 14/06/24.
//

# include "../Engine/Nodes/UI/Label.h"
#include "player.h"
#include "iostream"

using namespace Game;
class Score : public Engine::Nodes::Label
{
    public:
    Player *player;
     void idle(double deltaTime)
    {
        text = "Score: " + std::to_string((int )player->score);
    }
};