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
        float max_speed = 200;
        float acceleration = 150;

        Vector3 look_direction = Vector3::FORWARD;
        float rotation_speed = 0;
        float max_rotation_speed = 180 * PI / 180.0;
        float rotation_acceleration = 100 * PI / 180.0;


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

            SpaceShipMesh* model = new SpaceShipMesh();
            model->rotateAround(Vector3::UP, PI);
            addChild(model);

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
