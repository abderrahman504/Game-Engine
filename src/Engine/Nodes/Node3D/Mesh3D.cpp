#include "Mesh3D.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>

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
            delete[] indeces[i];
        }
        if(texCoords != nullptr){
            delete[] texCoords;
        }
        delete[] vertices;
        delete[] indeces;
        delete[] countIndeces;
        delete[] colors; // Free the color array
        delete material;
    }
}

float* Mesh3D::Vertices() { return vertices; }
unsigned int** Mesh3D::Indeces() { return indeces; }
int* Mesh3D::CountIndeces() { return countIndeces; }
int Mesh3D::CountPrimitives() { return countPrimitives; }
int Mesh3D::TexCoordsSize() { return texCoordsSize; }
float* Mesh3D::TexCoords() { return texCoords; }
float* Mesh3D::Colors() { return colors; } // Getter for colors

bool Mesh3D::LoadOBJ(const char* path, float** vertices, unsigned int*** indices, int** countIndices, int* countPrimitives, float** colors) {
    std::vector<float> vertice;
    std::vector<unsigned int> indice;
    std::vector<float> colorArray; // Vector to store colors
    std::ifstream in_file(path);

    if (!in_file.is_open()) {
        std::cerr << "ERROR::OBJLOADER::Could not open file." << std::endl;
        return false;
    }

    std::string line, prefix;
    while (std::getline(in_file, line)) {
        std::istringstream ss(line);
        ss >> prefix;

        if (prefix == "v") {
            float x, y, z, r, g, b;
            ss >> x >> y >> z >> r >> g >> b;
            vertice.push_back(x);
            vertice.push_back(y);
            vertice.push_back(z);
            colorArray.push_back(r); // R
            colorArray.push_back(g); // G
            colorArray.push_back(b); // B
        } else if (prefix == "f") {
            // break;
            std::string vertexStr;
            unsigned int vertexIndex[3];
            int i = 0;
            while (ss >> vertexStr) {
                std::istringstream vertexStream(vertexStr);
                std::string indexStr;
                std::getline(vertexStream, indexStr, '/');
                vertexIndex[i++] = std::stoi(indexStr) - 1;
            }
            for (int j = 0; j < 3; ++j) {
                indice.push_back(vertexIndex[j]);
            }
        }
    }

    in_file.close();
    verticesSize = vertice.size();
    *vertices = new float[vertice.size()];
    *indices = new unsigned int*[1];
    (*indices)[0] = new unsigned int[indice.size()];
    *countIndices = new int[1];
    (*countIndices)[0] = indice.size();
    *countPrimitives = 1;
    *colors = new float[colorArray.size()]; // Allocate memory for colors
    // std::cout<<"color array size: "<<colorArray.size()<<std::endl; // Print the size of the color array
    // std::cout<<"vertices size: "<<vertice.size()<<std::endl; // Print the size of the vertices array
    //   for (int i = 0; i < colorArray.size(); i+=3)
    //             {
    //                 std::cout <<"color "<< colorArray[i] << " " << colorArray[i+1] << " " << colorArray[i+2] << std::endl;
    //             }

    std::copy(vertice.begin(), vertice.end(), *vertices);
    std::copy(indice.begin(), indice.end(), (*indices)[0]);
    std::copy(colorArray.begin(), colorArray.end(), *colors); // Copy colors to the array

    return true;
}

long Mesh3D::VerticesSize() { return verticesSize; }
