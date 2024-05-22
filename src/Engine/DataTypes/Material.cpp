#include "Material.h"


using namespace Engine::DataTypes;

Material::Material(){}

Material::Material(Color color, float amb_dif, float emi, float spec, int shine){
    this->color = color;
    ambient_diffuse = amb_dif;
    emission = emi;
    specular = spec;
    shininess = shine;
}