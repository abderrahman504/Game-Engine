#ifndef MATERIAL_GUARD
#define MATERIAL_GUARD
#include "Color.h"

namespace Engine{
namespace DataTypes{

    struct Material{

        Color color = Color(); //Sets the color of the material. The fourth value is the alpha value.
        int shininess = 80; //Represents the shininess of the material.
        //All these values must be in range [0,1]
        float ambient_diffuse = 1; //Represents the percentage of ambient & diffuse light reflected by this material.
        float emission = 0; //Represents the percentage of light emitted by this material.
        float specular = 1; // Reperesents the percentage of specular light reflected by this material.
        
        Material();
        Material(Color color, float amb_dif, float emi, float spec, int shine);
        
    };
}}


#endif