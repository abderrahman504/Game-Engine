//
// Created by mado on 14/06/24.
//

# include "../Engine/Nodes/UI/Label.h"
#include "iostream"
class Score : public Engine::Nodes::Label
{
    public:
     void idle(double deltaTime)
    {
        text = "Score: " + std::to_string((float )deltaTime);
    }
};