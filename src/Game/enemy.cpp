//
// Created by AhmedSamir on 12/06/2024.
//

#include "enemy.h"

using namespace Game;
Enemy::Enemy() {

}
void Enemy::idle(double deltaTime) {
    std::vector<Node *> children= getChildren();
  for(int i=0;i<children.size();i++) {
      SpaceShipMesh *enemy = dynamic_cast<SpaceShipMesh *>(children[i]);
      if (player) { // Check if player is not a nullptr
          // Calculate the direction vector from the enemy to the player
          double dirX = player->position.x - enemy->position.x;
          double dirY = player->position.y - enemy->position.y;
          double dirZ = player->position.z - enemy->position.z;

          // Normalize the direction vector
          double length = std::sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);
          if (length > 0) { // Prevent division by zero
              dirX /= length;
              dirY /= length;
              dirZ /= length;

              // Move the enemy towards the player
              double speed = 10.0; // Adjust speed as necessary

                 enemy-> position.x += dirX * speed * deltaTime;

                  enemy->position.y += dirY * speed * deltaTime;

                  enemy-> position.z += dirZ * speed * deltaTime;
          }

          // Debug output
          std::cout << "Enemy Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
          std::cout << "Player Position: (" << player->position.x << ", " << player->position.y << ", "
                    << player->position.z << ")\n";
      }
  }
}

void Enemy::attachEnemy(SpaceShipMesh* player) {
this->player=player;

}