#include "SkyBox.h"
#include <iostream>
#include <algorithm> // for std::copy

using namespace Engine::Nodes;

Skybox::Skybox(float size) {
    this->size = size;
    GenerateSkyboxMesh();
    InitializeTextureCoords();
}

Skybox::~Skybox() {
    if (vertices) delete[] vertices;
    if (indeces) {
        for (int i = 0; i < countPrimitives; ++i) {
            delete[] indeces[i];
        }
        delete[] indeces;
    }
    if (countIndeces) delete[] countIndeces;
}

void Skybox::GenerateSkyboxMesh() {
    float skyboxVertices[] = {
        // positions
        -size,  size, -size,
        -size, -size, -size,
         size, -size, -size,
         size, -size, -size,
         size,  size, -size,
        -size,  size, -size,

        -size, -size,  size,
        -size, -size, -size,
        -size,  size, -size,
        -size,  size, -size,
        -size,  size,  size,
        -size, -size,  size,

         size, -size, -size,
         size, -size,  size,
         size,  size,  size,
         size,  size,  size,
         size,  size, -size,
         size, -size, -size,

        -size, -size,  size,
        -size,  size,  size,
         size,  size,  size,
         size,  size,  size,
         size, -size,  size,
        -size, -size,  size,

        -size,  size, -size,
         size,  size, -size,
         size,  size,  size,
         size,  size,  size,
        -size,  size,  size,
        -size,  size, -size,

        -size, -size, -size,
        -size, -size,  size,
         size, -size,  size,
         size, -size,  size,
        -size, -size,  size,
         size, -size, -size
    };

    vertices = new float[sizeof(skyboxVertices) / sizeof(float)];
    std::copy(skyboxVertices, skyboxVertices + sizeof(skyboxVertices) / sizeof(float), vertices);

    countPrimitives = 1;
    countIndeces = new int[countPrimitives]{ 36 };
    indeces = new unsigned int*[countPrimitives];
    indeces[0] = new unsigned int[36];
    for (int i = 0; i < 36; ++i) {
        indeces[0][i] = i;
    }
}

void Skybox::InitializeTextureCoords() {
    // Texture coordinates for each face (assuming normalized coordinates)
    // Right face
    textureCoords[0][0][0] = 1.0f; textureCoords[0][0][1] = 1.0f;
    textureCoords[0][1][0] = 1.0f; textureCoords[0][1][1] = 0.0f;
    textureCoords[0][2][0] = 0.0f; textureCoords[0][2][1] = 0.0f;
    textureCoords[0][3][0] = 0.0f; textureCoords[0][3][1] = 1.0f;

    // Left face
    textureCoords[1][0][0] = 0.0f; textureCoords[1][0][1] = 1.0f;
    textureCoords[1][1][0] = 1.0f; textureCoords[1][1][1] = 1.0f;
    textureCoords[1][2][0] = 1.0f; textureCoords[1][2][1] = 0.0f;
    textureCoords[1][3][0] = 0.0f; textureCoords[1][3][1] = 0.0f;

    // Top face
    textureCoords[2][0][0] = 0.0f; textureCoords[2][0][1] = 0.0f;
    textureCoords[2][1][0] = 0.0f; textureCoords[2][1][1] = 1.0f;
    textureCoords[2][2][0] = 1.0f; textureCoords[2][2][1] = 1.0f;
    textureCoords[2][3][0] = 1.0f; textureCoords[2][3][1] = 0.0f;

    // Bottom face
    textureCoords[3][0][0] = 1.0f; textureCoords[3][0][1] = 1.0f;
    textureCoords[3][1][0] = 0.0f; textureCoords[3][1][1] = 1.0f;
    textureCoords[3][2][0] = 0.0f; textureCoords[3][2][1] = 0.0f;
    textureCoords[3][3][0] = 1.0f; textureCoords[3][3][1] = 0.0f;

    // Back face
    textureCoords[4][0][0] = 1.0f; textureCoords[4][0][1] = 1.0f;
    textureCoords[4][1][0] = 0.0f; textureCoords[4][1][1] = 1.0f;
    textureCoords[4][2][0] = 0.0f; textureCoords[4][2][1] = 0.0f;
    textureCoords[4][3][0] = 1.0f; textureCoords[4][3][1] = 0.0f;

    // Front face
    textureCoords[5][0][0] = 0.0f; textureCoords[5][0][1] = 0.0f;
    textureCoords[5][1][0] = 1.0f; textureCoords[5][1][1] = 0.0f;
    textureCoords[5][2][0] = 1.0f; textureCoords[5][2][1] = 1.0f;
    textureCoords[5][3][0] = 0.0f; textureCoords[5][3][1] = 1.0f;
}

void Skybox::LoadSkyboxTextures(const std::vector<std::string>& faces) {
    if (faces.size() != 6) {
        std::cerr << "Skybox requires exactly 6 textures." << std::endl;
        return;
    }

    for (int i = 0; i < 6; ++i) {
        if (!textures[i].loadFromFile(faces[i])) {
            std::cerr << "Failed to load texture: " << faces[i] << std::endl;
            return;
        }
    }
}

void Skybox::Draw() {
    glColor4f(65 / 256.0, 175 / 256.0, 239 / 256.0,1);
    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);

    for (int i = 0; i < 6; ++i) {
        glTexCoordPointer(2, GL_FLOAT, 0, textureCoords[i]);
        textures[i].bind();
        glDrawElements(GL_TRIANGLES, countIndeces[0], GL_UNSIGNED_INT, indeces[0]);
    }

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
