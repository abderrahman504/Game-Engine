// Texture.h




#ifndef GAME_ENGINE_TEXTURE_H
#define GAME_ENGINE_TEXTURE_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>
class Texture {

    sf::Image *image;
public:
    Texture();
    ~Texture();
    GLuint textureID;


    bool loadFromFile(const std::string& filename); // Load texture from file
    void bind(); // Bind texture for rendering

private:
};

#endif 