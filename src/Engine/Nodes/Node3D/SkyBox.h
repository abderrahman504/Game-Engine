#ifndef SKYBOX_GUARD
#define SKYBOX_GUARD

#include "Node3D.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace Engine::Nodes;

class SkyBox : public Node3D {
public:
    // Constructor
    SkyBox();

    // Vertex data
    bool isdrawn;
    static const GLfloat skyboxVertices[];
    static const GLfloat TextureCoords[6][4][2];
    static const GLuint  skyboxIndices[];

    // Texture file paths for the skybox
    std::vector<std::string> faces;
};

#endif
