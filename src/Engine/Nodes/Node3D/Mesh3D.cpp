#include "Mesh3D.h"
using namespace Engine::Nodes;

void Mesh3D::Scale(float scaleFactor) {
    // Iterate through all vertices and scale them
    for (int i = 0; i < countPrimitives; ++i) {
        for (int j = 0; j < countIndeces[i]; ++j) {
            int vertexIndex = indeces[i][j];
            vertices[vertexIndex * 3] *= scaleFactor;        // Scale X coordinate
            vertices[vertexIndex * 3 + 1] *= scaleFactor;    // Scale Y coordinate
            vertices[vertexIndex * 3 + 2] *= scaleFactor;    // Scale Z coordinate
        }
    }
}

Mesh3D::Mesh3D(){
    setName("Mesh3D");
}
Mesh3D::~Mesh3D(){
    if(vertices != nullptr){
        for(int i = 0; i < countPrimitives; i++){
            delete[] vertices;
            delete[] indeces[i];
        }
        delete[] vertices;
        delete[] indeces;
        delete[] countIndeces;
        delete material;
    }
}
float* Mesh3D::Vertices(){return vertices;}
unsigned int** Mesh3D::Indeces(){return indeces;}
int* Mesh3D::CountIndeces(){return countIndeces;}
int Mesh3D::CountPrimitives(){return countPrimitives;}
bool Mesh3D::LoadOBJ(const char* path) {
    std::vector<float> temp_vertices;
    std::vector<unsigned int> temp_indices;
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream s(line);
        std::string type;
        s >> type;
        if (type == "v") {
            float x, y, z;
            s >> x >> y >> z;
            temp_vertices.push_back(x);
            temp_vertices.push_back(y);
            temp_vertices.push_back(z);
        } else if (type == "f") {
            for (int i = 0; i < 3; ++i) {
                unsigned int vertexIndex, textureIndex, normalIndex;
                char slash;
                s >> vertexIndex >> slash >> textureIndex >> slash >> normalIndex;
                temp_indices.push_back(vertexIndex - 1); // Adjust for OpenGL indexing
            }
        }
    }

    file.close();

    // Allocate memory for vertices
    vertices = new float[temp_vertices.size()];
    std::copy(temp_vertices.begin(), temp_vertices.end(), vertices);

    // Allocate memory for indices
    countPrimitives = temp_indices.size() / 3;
    indeces = new unsigned int*[countPrimitives];
    countIndeces = new int[countPrimitives];
    for (int i = 0; i < countPrimitives; ++i) {
        indeces[i] = new unsigned int[3];
        countIndeces[i] = 3;
        for (int j = 0; j < 3; ++j) {
            indeces[i][j] = temp_indices[i * 3 + j];
        }
    }

    return true;
}
