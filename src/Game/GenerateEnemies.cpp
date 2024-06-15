//
// Created by mado on 15/06/24.
//
#include "enemy.h"
#include "../Engine/Nodes/Node.h"

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
        attachChild(enemy);
    }

};
