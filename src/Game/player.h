//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_PLAYER_H
#define GAME_ENGINE_PLAYER_H

#include "../Engine.h"
#include <stdio.h>

namespace Game{
    class Player : public Engine::Nodes::CollisionBody3D{
        int health;
        float speed;
        float rotationSpeed;
        float acceleration;
        float rotationAcceleration;

        public:
        Player();
        Mesh3D* mesh;
        void attachMesh(Engine::Nodes::Mesh3D* mesh);
        void move();



    };
}


#endif //GAME_ENGINE_PLAYER_H
