#ifndef MATERIAL_GUARD
#define MATERIAL_GUARD
#include "Color.h"
#include "Texture.h"
#include <string>
#include <iostream>

namespace Engine
{
    namespace DataTypes
    {

        class Material
        {

        public:
            Color color = Color();
            int shininess = 80;
            float ambient_diffuse = 1; // Represents the percentage of ambient & diffuse light reflected by this material.
            float emission = 0;        // Represents the percentage of light emitted by this material.
            float specular = 1;

            void setTexture(const std::string &texturePath);
            void setTextureCoordinates(float *texCoords, int texCoordsSize);
            float *textureCoordinates;
            Texture *texture = nullptr; // The texture of the material.
            void bindTexture();
            Material();
            ~Material();
            Material(Color color, float amb_dif, float emi, float spec, int shine);

        private:
            int textureCoordinatesSize;
        };
    }
}

#endif