// Texture.cpp
#include "Texture.h"

Texture::Texture() {
    image=nullptr;
}

Texture::~Texture() {}

bool Texture::loadFromFile(const std::string& filename) {
    if (image == nullptr) {
        image = new sf::Image();
        if (!image->loadFromFile(filename)) {
        std::cerr << "Error loading texture." << std::endl;
        exit(1);
    }
    }


    std::cout << "Loaded texture: " << filename << std::endl;


    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getSize().x, image->getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getPixelsPtr());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, textureID);
}