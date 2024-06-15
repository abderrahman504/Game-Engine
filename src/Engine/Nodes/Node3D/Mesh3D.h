#ifndef MESH3D_GUARD
#define MESH3D_GUARD
#include "Node3D.h"
#include "../../DataTypes.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
namespace Engine{
namespace Nodes{

    class Mesh3D : public Node3D
    {
        public:
        DataTypes::Material *material = new DataTypes::Material();
        protected:
        float* vertices = nullptr;
        unsigned int** indeces = nullptr;
        int* countIndeces = nullptr;
        int countPrimitives = 0;
        float *texCoords = nullptr;
        int texCoordsSize = 0;
        float *colors = nullptr; // Array to store colors

        public:
        Mesh3D();
        ~Mesh3D();
        float* Vertices();
        unsigned int** Indeces();
        int* CountIndeces();
        int CountPrimitives();
        int TexCoordsSize();
        float* TexCoords();
        float* Colors(); // Getter for colors
        bool LoadOBJ(const char* path, float** vertices, unsigned int*** indices, int** countIndices, int* countPrimitives, float** colors);
        void Scale(float scaleFactor);
    };
}}

#endif