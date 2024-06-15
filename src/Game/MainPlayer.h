//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_MAINPLAYER_H
#define GAME_ENGINE_MAINPLAYER_H


#include "../Engine.h"
#include <stdio.h>
#include "player.h"
#include "SoundManager.h"
namespace Game{
    class MainPlayer : public Player{
    private:
        int score;
        int ammo;
        Vector3 velocity = Vector3::ZERO;
        const float damping = 0.95f;     
        protected:
        void idle(double deltaTime);
        void onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info);
        public:
        MainPlayer(float speed, float acceleration, float rotationSpeed, float rotationAcceleration, int health, float maxSpeed) {
            score = 0;
            ammo = 2;
            this->speed = speed;
            this->acceleration = acceleration;
            this->rotationSpeed = rotationSpeed;
            this->rotationAcceleration = rotationAcceleration;
            this->health = health;
            this->maxSpeed = maxSpeed;
            collisionLayer = 0b0001; //Player exists on layer 1
            collisionMask = 0b0010; //Player scans for layer 2
            SphereCollider *collider = new SphereCollider(15);

            setName("Player");
            addChild(collider);

        }
        void shoot();
        void destroy();
        void setScore(int score);
        int getScore();
        void addScore(int score);
        void addHealth(int health);
        void setAmmo(int ammo);
    };

}

#endif //GAME_ENGINE_MAINPLAYER_H
