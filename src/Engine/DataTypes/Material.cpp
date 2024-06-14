#include "Material.h"
#include <string.h>

using namespace Engine::DataTypes;

Material::Material() : textureCoordinates(nullptr), textureCoordinatesSize(0)
{
}
Material::Material(Color color, float amb_dif, float emi, float spec, int shine) : textureCoordinates(nullptr), textureCoordinatesSize(0)
{
    this->color = color;
    ambient_diffuse = amb_dif;
    emission = emi;
    specular = spec;
    shininess = shine;
    // texture = new Texture();
}
Material::~Material()
{
}

void Material::setTexture(const std::string &texturePath)
{
    if (texture == nullptr) {
        texture = new Texture();
    }
    if (!texture->loadFromFile(texturePath))
    {
        // Handle texture loading failure
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
}

void Material::setTextureCoordinates(float *texCoords, int texCoordsSize)
{
    // Clear old texture coordinates if any
    delete[] textureCoordinates;

    // Allocate new texture coordinates array
    textureCoordinates = new float[texCoordsSize];
    textureCoordinatesSize = texCoordsSize;

    // Copy new texture coordinates
    memcpy(textureCoordinates, texCoords, texCoordsSize * sizeof(float));
}

void Material::bindTexture()
{
    texture->bind(); // Bind using Texture class
}
