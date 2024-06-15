//
// Created by mado on 15/06/24.
//
#include "enemy.h"
#include "../Engine/Nodes/Node.h"
#include <random>

using namespace Game;
class GenerateEnemies : public Engine::Nodes::Node {
    public:

    void idle(double deltaTime) {

    }
    void addEnemy() {
        Enemy *enemy = new Enemy();
        enemy->Level = 1;
        enemy->x = generate_random_number();
        enemy->position = Vector3(enemy->x, 0, 0);
        addChild(enemy);
    }

    int generate_random_number() {
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(0, 100); // Define the range

    return distr(gen); // Generate the random number
}

};
