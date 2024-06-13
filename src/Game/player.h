//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_PLAYER_H
#define GAME_ENGINE_PLAYER_H

#include "../Engine.h"
#include <stdio.h>
#include "Bullet.h"

namespace Game{
    class Player : public Engine::Nodes::CollisionBody3D{
        protected:
        int health;
        float speed;
        float acceleration;
        float rotationSpeed;
        float maxSpeed;
        float rotationAcceleration;
        public:
        Player(){

        };
        void shoot();
        void destroy();
    };
}


#endif //GAME_ENGINE_PLAYER_H
