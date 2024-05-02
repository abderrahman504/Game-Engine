#include "Engine.h"
#include <stdio.h>

using namespace Engine;
using namespace Engine::DataTypes;

int main(int argc, char** argv)
{
    Vector2 vec = Vector2::ZERO;
    printf("vec = (%f, %f)", vec.x, vec.y);

    initEngine(argc, argv);
    return 0;
}
