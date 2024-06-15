


#ifndef  GAME_ENGINE_PICKABLEGENRATOR_H
#define  GAME_ENGINE_PICKABLEGENRATOR_H



#include "../Engine.h"
#include <stdio.h>
#include "Pickable.h"
#include "Bullet.h"

#include "vector"




namespace Game{
    class PickabelGenerator{
        // static std::vector<Pickable*> picks;

        public:
        static void generate(Node* node, int number){
            for(int i = 0; i < number; i++){

                //genrate random position for the pickable
                int x = rand() % 500 - 10;
                int y = rand() % 500 - 10;
                int z = rand() % 500- 10;

                // gerate random index for the pickable
                int index = rand() % 5;
                int health = 10;

                char* path;
                if (index ==0 || index == 1|| index == 2){
                    path = BULLETS_DATA[index].txtPath;

                }
                else if(index == 3){
                    path = "../resources/images/health.png";
                    health = 50;
                }
                else if(index == 4){
                    path = "../resources/images/coin.jpeg";
                    health = 20;
                }


                Pickable* pick = new Pickable(Vector3(x,y,z),path,1,50,5000,health,index);
                pick->setName("Pickable");
                // picks.push_back(pick);
                node->addChild(pick);

            }

        }
        static void destroy(){
            // for(int i = 0; i < picks.size(); i++){
            //     picks[i]->destroy();
            // }
            // picks.clear();

        }

    };
}


#endif // GAME_ENGINE_PICKABLEGENRATOR_H