//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_ENEMY_H
#define GAME_ENGINE_ENEMY_H

#include "../Engine.h"
#include <stdio.h>

#include "player.h"


namespace Game {
    class Enemy : public Player {

    public:
        Enemy();
        void move();
        void attachEnemy(Player* player);
    };
}


#endif //GAME_ENGINE_ENEMY_H
