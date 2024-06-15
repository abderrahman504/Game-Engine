//
// Created by AhmedSamir on 12/06/2024.
//

#include "enemy.h"
#include "Bullet.h"
using namespace Game;

Enemy::Enemy() 
{
    collisionLayer = 0b0010; //Enemy exists on layer 2
    collisionMask = 0; // Enemy doesn't scan for any layers
    setName("Enemy");
}


void Enemy::idle(double deltaTime) {
    if (player != nullptr) { // Check if player is not a nullptr

        // Calculate the direction vector from the enemy to the player
        Vector3 dir = player->position - position;
        float distance = dir.length();

        if(distance <= min_distance_to_player)
        {
            // Slow the enemy down
            velocity = velocity - velocity.normalize() * acceleration * deltaTime;
            if(velocity.length() < acceleration * deltaTime)
                velocity = Vector3::ZERO;
        }
        else
        {
            //Move towards the player
            dir = dir.normalize();

            velocity = velocity + dir * acceleration * deltaTime;
            if(velocity.length() > max_speed)
                velocity = velocity.normalize() * max_speed;
        }
        position = position + velocity * deltaTime;

        // rotate the enemy towards the player
        Vector3 dir_to_player = dir;
        Vector3 forward = getForward();
        float travel_angle = forward.angleTo(dir_to_player);
        Vector3 spin_vec = forward.cross(dir_to_player);

        //Figure out whether to rotate faster towards the player or slow down
        if(rotation_speed == 0 && travel_angle != 0)
        {
            //accelerate rotation
            rotation_speed += rotation_acceleration * deltaTime;
            if(rotation_speed > max_rotation_speed)
                rotation_speed = max_rotation_speed;
        }
        else
        {
            float travel_time = travel_angle / rotation_speed;
            float halting_time = rotation_speed / rotation_acceleration;
            if(travel_time < halting_time)
            {
                //decelerate rotation
                rotation_speed -= rotation_acceleration * deltaTime;
                if(rotation_speed < 0)
                    rotation_speed = 0;
            }
            else
            {
                //accelerate rotation
                rotation_speed += rotation_acceleration * deltaTime;
                if(rotation_speed > max_rotation_speed)
                    rotation_speed = max_rotation_speed;
            }

        }
        if(rotation_speed != 0)
        {
            float rotation = rotation_speed * deltaTime;
            if(rotation > travel_angle)
                rotation = travel_angle;
            rotateAround(spin_vec, rotation);
        }

        // Shoot at player
        timeSinceLastShot += deltaTime;
        if (timeSinceLastShot >= shootingInterval) {
            std::cout << "Enemy is shooting" << std::endl;
             this->shoot();
            timeSinceLastShot = 0.0; // Reset the timer
        }
    }
}

void Enemy::shoot() {
    Bullet *bullet = new Bullet(1, 1, 100, 50, 100, 20);
    //Set bullet position and move direction
    bullet->position = position;
    bullet->orientation = orientation;
    bullet->lookTowards(getForward(), getUp());
    bullet->moveDir = getForward();
    //Set bullet collision layer and mask to collide only with player and not with enemy
    bullet->collisionLayer = 0b0100; //Bullet exists on layer 3
    bullet->collisionMask =  0b0001; //Bullet scans layer 1 (the player exists in that layer)

    //  std::vector < Node * > children = getChildren();
    //  for (int i = 0; i < children.size(); i++) {
    //      SpaceShipMesh *enemy = dynamic_cast<SpaceShipMesh *>(children[i]);
    //      if (enemy == nullptr) continue;
    //      bullet->position = enemy->position;
    //      bullet->orientation = enemy->orientation;
    //      bullet->lookTowards(enemy->getForward(), Vector3::UP);
    //      bullet->moveDir = enemy->getForward();
    //  }
    bullet->setName("Bullet");
    Parent()->addChild(bullet);
}


void Enemy::attachEnemy(CollisionBody3D *player) {
    this->player = player;
}


void Enemy::destroy() {
    queueFree();
}

void Enemy::onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info) {
    std::cout << "Enemy collided with " << other->getName() << std::endl;
    if (dynamic_cast<Bullet*>(other) != nullptr) {
        Bullet *bullet = dynamic_cast<Bullet *>(other);
        bullet->destroy();
        //if Bullet is intended to hit player 
        if (bullet->collisionMask == 1) return;
        
        health -= bullet->getDamage();
        if (health <= 0) {
            destroy();
        }
    }
}