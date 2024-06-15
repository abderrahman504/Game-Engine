

#ifndef SKYBOX_GUARD
#define SKYBOX_GUARD
#include "Mesh3D.h"
#include "Node3D.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "../../DataTypes.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include "../../DataTypes.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Engine {
namespace Nodes {

class Skybox : public Mesh3D {
public:
    Skybox(float size);
    ~Skybox();
    void LoadSkyboxTextures(const std::vector<std::string>& faces);
    void Draw();
    void InitializeTextureCoords();

private:
    float size;
    float textureCoords[6][4][2];
    Texture textures[6];
    void GenerateSkyboxMesh();
};

}}

#endif

