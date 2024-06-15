//
// Created by mado on 14/06/24.
//
#include "../Engine/Nodes/UI/Quad.h"
#include "player.h"
using namespace Game;
class HealthBar : public Engine::Nodes::Quad
{
public:
    Player *player;
    void attachPlayer(Player *player)
    {
        this->player = player;
    }


protected:
   void idle(double deltaTime)
   {
        if(size.x>0)
          size.x-=0.01*deltaTime;
   }


};