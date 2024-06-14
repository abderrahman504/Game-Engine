#ifndef ROOT_GUARD
#define ROOT_GUARD

#include "../Engine.h"


class Root : public Node
{

    public:

    CollisionBody3D* player;
    int score = 0;
    int enemyCount = 0;
    

    Root();


    protected:

    void idle(double deltaTime);



};

#endif