#include "Engine.h"
#include <stdio.h>

using namespace Engine;
using namespace Engine::DataTypes;

int main(int argc, char** argv)
{
    Vector2 vec = Vector2(0,0);

    printf("main started\n");
    initEngine(argc, argv);
    printf("main finished\n");
    return 0;
}
