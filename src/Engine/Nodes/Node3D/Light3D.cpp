#include "Light3D.h"

using namespace Engine::Nodes;

Light3D::Light3D() : Node3D(){
    setName("Light3D");
}

Light3D::Light3D(DataTypes::Color color, float ambient, float diffuse, float specular) : Node3D(){
    setName("Light3D");
    this->color = color;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}