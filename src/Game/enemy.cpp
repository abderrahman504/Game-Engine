//
// Created by AhmedSamir on 12/06/2024.
//

#include "enemy.h"
#include <random>
using namespace Game;
Enemy::Enemy() {
    health = 100;
    speed = 10;
    acceleration = 10;
    rotationSpeed = 10;
    maxSpeed = 10;
    rotationAcceleration = 10;
    player = nullptr;
    shootingInterval = 3.0; // Adjust as necessary
    timeSinceLastShot = 0.0;
    collisionLayer = 0; //Enemy exists on layer 2
    collisionMask = 0; // Enemy doesn't scan for any layers
    Level = 1;
    x=0;

    setName("Enemy");
}
int Enemy::generate_random_number() {
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(0, 100); // Define the range

    return distr(gen); // Generate the random number
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

     std::vector < Node * > children = getChildren();
     for (int i = 0; i < children.size(); i++) {
         SpaceShipMesh *enemy = dynamic_cast<SpaceShipMesh *>(children[i]);
         if (enemy == nullptr) continue;
         bullet->position = enemy->position;
         bullet->orientation = enemy->orientation;
         bullet->lookTowards(enemy->getForward(), Vector3::UP);
         bullet->moveDir = enemy->getForward();
     }
    bullet->setName("Bullet");
    Parent()->addChild(bullet);
}


void Enemy::idle(double deltaTime) {
    std::vector<Node *> children = getChildren();
    switch (Level) {
    case 1:
        if(children.size() <3) {
            addEnemy();
            x+=30;
        }
        break;
    case 2:
        if(children.size() <6) {
            addEnemy();
            x+=30;
        }
        break;
    case 3:
        if(children.size() <9) {
            addEnemy();
            x+=30;
        }
        break;


    }
    if (player) {
        std::cout<< "Enemy is moving" << std::endl;
            // Check if player is not a nullptr
            // Calculate the direction vector from the enemy to the player
            Vector3 dir = player->position - position;

            // Normalize the direction vector
            dir = dir.normalize();

            // Move the enemy towards the player
            double speed = 20.0; // Adjust speed as necessary
            position = position + dir * speed * deltaTime;

            // rotate the enemy towards the player
            Vector3 enemyForward = dir;
            Vector3 enemyUp = Vector3(0, 1, 0);
            lookTowards(enemyForward, enemyUp);

            timeSinceLastShot += deltaTime;
            if (timeSinceLastShot >= shootingInterval) {
                std::cout << "Enemy is shooting" << std::endl;
                this->shoot();
                timeSinceLastShot = 0.0; // Reset the timer
            }

    }
}

void Enemy::attachEnemy(Player *player) {
    this->player = player;
}

SpaceShipMesh *Enemy::drawSpaceship(float baseWidth, float baseHeight, float height, int resolution, Vector3 vector3, bool isEnemy) {
    SpaceShipMesh *spaceship = new SpaceShipMesh(baseWidth, baseHeight, height, resolution);

    Material *spaceshipMaterial = spaceship->material;
    // set color of spaceship to be red
    if (isEnemy)
        spaceshipMaterial->color = Color::fromRGBFloat(1, 0, 0, 1);
    else
        spaceshipMaterial->color = Color::fromRGBFloat(0, 0, 1, 1);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship->position = vector3;
    spaceship->setName("Spaceship");

    SpaceShipMesh *spaceship1 = new SpaceShipMesh(baseWidth / 1.5, baseHeight / 3, height / 2, resolution);
    spaceshipMaterial = spaceship1->material;
    // set color of spaceship to be red
    spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship1->position = Vector3(5, 0, height / 5.5);

    spaceship1->setName("right wing");
    SpaceShipMesh *spaceship2 = new SpaceShipMesh(baseWidth / 1.5, baseHeight / 3, height / 2, resolution);
    spaceshipMaterial = spaceship2->material;
    // set color of spaceship to be red
    spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceship2->position = Vector3(-5, 0, height / 5.5);
    spaceship2->setName("left wing");

    SphereMesh *spaceshiphead = new SphereMesh(height / 10, resolution);
    spaceshipMaterial = spaceshiphead->material;
    // set color of spaceship to be red
    spaceshipMaterial->color = Color::fromRGBFloat(1.0f, 1.0f, 0.0f, 1.0f);
    spaceshipMaterial->ambient_diffuse = 1;
    spaceshipMaterial->shininess = 0;
    spaceshipMaterial->specular = 0;
    spaceshiphead->position = Vector3(0, 1.2, -7.5);
    spaceshiphead->setName("head");

    spaceship->addChild(spaceship1);
    spaceship->addChild(spaceship2);
    spaceship->addChild(spaceshiphead);

    return spaceship;
}
void Enemy::addEnemy() {
    addChild(drawSpaceship(10, 10, 20, 100, Vector3(x, 0, 0), true));
}


void Enemy::destroy() {
    std::vector < Node * > children = getChildren();
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->getName() == "Bullet") {
            Bullet *bullet = dynamic_cast<Bullet *>(children[i]);
            bullet->destroy();
        }
    }
    queueFree();
}

void Enemy::onCollision(Engine::Nodes::CollisionBody3D *other, Engine::CollisionInfo info) {
    // std::cout << "Enemy collided with " << other->getName() << std::endl;
    // if (other->getName() == "Bullet") {
    //     Bullet *bullet = dynamic_cast<Bullet *>(other);
    //     bullet->destroy();
    //     if (bullet->Parent()->getName() == "Enemy") return;
    //     health -= bullet->getDamage();
    //     if (health <= 0) {
    //         destroy();
    //     }
    // }
    // if (other->getName() == "Player") {
    //     health -= 10;
    //     if (health <= 0) {
    //         destroy();
    //     }
    // }
}