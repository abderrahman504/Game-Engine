#include "Material.h"


using namespace Engine::DataTypes;

Material::Material(){}

Material::Material(float r, float g, float b, float a, float amb, float diff, float shine){
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
    ambient = amb;
    diffuse = diff;
    shininess = shine;
}