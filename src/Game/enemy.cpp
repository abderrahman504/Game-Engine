//
// Created by AhmedSamir on 12/06/2024.
//

#include "enemy.h"
#include "Bullet.h"
using namespace Game;

// static ConeMesh *drawSpaceship(float baseWidth, float baseHeight, float height, bool isEnemy);

Enemy::Enemy() 
{
    Level = 1;
    x=0;
    collisionLayer = 0b0010; //Enemy exists on layer 2
    collisionMask = 0; // Enemy doesn't scan for any layers
    //Create model
    // ConeMesh *spaceship = drawSpaceship(10, 10, 20, true);
    SpaceShipMesh* spaceship = new SpaceShipMesh();
    spaceship->rotateAround(Vector3::UP, PI);
    spaceship->material->color = Color::WHITE;
    spaceship->material->ambient_diffuse = 1;
    spaceship->material->emission = 1;

    addChild(spaceship);
    //Create collider
    SphereCollider* collider = new SphereCollider(20);
    collider->radius = 10;
    addChild(collider);

    setName("Enemy");
}






void Enemy::idle(double deltaTime) {
    if (player != nullptr)
    { // Check if player is not a nullptr

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
    Bullet *bullet = new Bullet(0.5, 100, 200, 5, 5,0,false);
    bullet->position = position + getForward() * 2;
    bullet->orientation = orientation;
    bullet->lookTowards(getForward(), Vector3::UP);
    bullet->moveDir = getForward();
    this->Parent()->addChild(bullet);
    //Set bullet collision layer and mask to collide only with player and not with enemy
    bullet->collisionLayer = 0b0100; //Bullet exists on layer 3
    bullet->collisionMask =  0b0001; //Bullet scans layer 1 (the player exists in that layer)

    bullet->setName("Bullet");

    //Add collider to bullet
    SphereCollider *collider = new SphereCollider(0.5);
    collider->setName("Bullet");
    bullet->addChild(collider);
    bullet->shooter = false;

    this->Parent()->addChild(bullet);
}


void Enemy::attachEnemy(CollisionBody3D *player) {
    this->player = player;
}

void Enemy::addEnemy() {
    // addChild(drawSpaceship(10, 10, 20, 100, Vector3(x, 0, 0), true));
}


void Enemy::destroy() {
    queueFree();
}

void Enemy::onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info) {
    // std::cout << "Enemy collided with " << other->getName() << std::endl;
    // if (dynamic_cast<Bullet*>(other) != nullptr) {
    //     Bullet *bullet = dynamic_cast<Bullet *>(other);
    //     bullet->destroy();
    //     //if Bullet is intended to hit player 
    //     if (bullet->collisionMask == 1) return;
        
    //     health -= bullet->getDamage();
    //     if (health <= 0) {
    //         destroy();
    //     }
    // }
}






// static ConeMesh *drawSpaceship(float baseWidth, float baseHeight, float height, bool isEnemy)
// {
    
//     ConeMesh *spaceship = new ConeMesh(baseWidth/2, baseHeight/2, height, 50);

//     Material *spaceshipMaterial = spaceship->material;
//     // set color of spaceship to be red
//     if (isEnemy)
//         spaceshipMaterial->color = Color::fromRGBFloat(1, 0, 0, 1);
//     else
//         spaceshipMaterial->color = Color::fromRGBFloat(0, 0, 1, 1);
//     spaceshipMaterial->ambient_diffuse = 1;
//     spaceshipMaterial->shininess = 0;
//     spaceshipMaterial->specular = 0;
//     spaceship->setName("Spaceship Model");
//     spaceship->lookTowards(Vector3::DOWN, Vector3::FORWARD);

//     ConeMesh *right_wing = new ConeMesh(baseWidth / 4, baseHeight / 4, height / 3, 50);
//     spaceshipMaterial = right_wing->material;
//     // set color of spaceship to be red
//     spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
//     spaceshipMaterial->ambient_diffuse = 1;
//     spaceshipMaterial->shininess = 0;
//     spaceshipMaterial->specular = 0;
//     right_wing->position = Vector3(baseWidth / 2, height * 0.2, 0);
//     right_wing->setName("right wing");

//     ConeMesh *left_wing = new ConeMesh(baseWidth / 4, baseHeight / 4, height / 3, 50);
//     spaceshipMaterial = left_wing->material;
//     spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
//     spaceshipMaterial->ambient_diffuse = 1;
//     spaceshipMaterial->shininess = 0;
//     spaceshipMaterial->specular = 0;
//     left_wing->position = Vector3(-baseWidth / 2, height * 0.2, 0);
//     left_wing->setName("left wing");


//     spaceship->addChild(right_wing);
//     spaceship->addChild(left_wing);
//     // spaceship->addChild(spaceshiphead);

//     return spaceship;
// }