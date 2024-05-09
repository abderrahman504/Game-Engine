#ifndef MATERIAL_GUARD
#define MATERIAL_GUARD

namespace Engine{
namespace DataTypes{

    struct Material{
        float color[4] = {0,0,0,1}; //Sets the color of the material. The fourth value is the alpha value.
        float ambient = 1; //Represents the percentage of ambient light reflected by this material.
        float diffuse = 1; // Reperesents the percentage of diffuse light reflected by this material.
        float shininess = 1; //Represents the percentage of specular light reflected by this material.
        
        Material();
        Material(float r, float g, float b, float a, float amb, float diff, float shine);
        
    };
}}


#endif