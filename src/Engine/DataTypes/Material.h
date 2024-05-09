#ifndef MATERIAL_GUARD
#define MATERIAL_GUARD

namespace Engine{
namespace DataTypes{

    struct Material{
        float color[4] = {0,0,0,1}; //Sets the color of the material. The fourth value is the alpha value.
        //All these values must be in range [0,1]
        float ambient_diffuse = 1; //Represents the percentage of ambient & diffuse light reflected by this material.
        float specular = 1; // Reperesents the percentage of specular light reflected by this material.
        float shininess = 1; //Represents the shininess of the material
        
        Material();
        Material(float r, float g, float b, float a, float amb, float spec, float shine);
        
    };
}}


#endif