//
// Created by mado on 15/06/24.
//
#include "enemy.h"
#include "../Engine/Nodes/Node.h"
#include "random"

using namespace Game;
class GenerateEnemies : public Engine::Nodes::Node {
    public:
    int Level = 1;
    Player *player;
    int generate_random_number() {
        std::random_device rd; // Obtain a random number from hardware
        std::mt19937 gen(rd()); // Seed the generator
        std::uniform_int_distribution<> distr(0, 1000); // Define the range

        return distr(gen); // Generate the random number
    }

    void idle(double deltaTime) {
        std::vector<Node *> children = getChildren();
        switch (Level) {
            case 1:
                if (children.size() < 3) {
                    addEnemy();


                }
                break;
            case 2:
                if (children.size() < 6) {
                    addEnemy();

                }
                break;

            case 3:
                if (children.size() < 9) {
                    addEnemy();

                }
                break;
        }
    }
   void attachEnemy(Player *player) {
        this->player = player;
    }
    void addEnemy() {
        Enemy *enemy = new Enemy();
        enemy->Level = 1;
        enemy->position = Vector3(generate_random_number(), 0, 0);
        enemy->attachEnemy(player);
        addChild(enemy);
    }


};
