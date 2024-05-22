#ifndef LIGHT3D_GUARD
#define LIGHT3D_GUARD
#include "Node3D.h"
#include "../../DataTypes.h"

namespace Engine{
namespace Nodes{

    class Light3D : public Node3D
    {
        public:
        Light3D();
        Light3D(DataTypes::Color color, float ambient, float diffuse, float specular);
        DataTypes::Color color = Color::WHITE; //The color of the light
        float ambient = 1; //Amount of ambient light produced by this light
        float diffuse = 1; //Amount of diffuse light produced by this light
        float specular = 1; //Amount of specular light produced by this light
            
    };
}}

#endif