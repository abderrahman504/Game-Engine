//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_MAINPLAYER_H
#define GAME_ENGINE_MAINPLAYER_H


#include "../Engine.h"
#include <stdio.h>
#include "player.h"
namespace Game{
    class MainPlayer : public Player{
    private:
        int score;
        Vector3 velocity = Vector3::ZERO;
        const float damping = 0.95f;      // Adjust as necessary
        protected:
        void idle(double deltaTime);
        void onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info);
        public:
        MainPlayer(float speed, float acceleration, float rotationSpeed, float rotationAcceleration, int health, float maxSpeed) {
            score = 0;
            this->speed = speed;
            this->acceleration = acceleration;
            this->rotationSpeed = rotationSpeed;
            this->rotationAcceleration = rotationAcceleration;
            this->health = health;
            this->maxSpeed = maxSpeed;
        }
        void shoot();
        void destroy();
    };

}

#endif //GAME_ENGINE_MAINPLAYER_H