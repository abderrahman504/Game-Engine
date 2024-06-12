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
        //The vertices of the mesh
        float* vertices = nullptr;
        //The indeces of the mesh
        unsigned int** indeces = nullptr;
        int* countIndeces = nullptr;
        int countPrimitives = 0;

        public:
        Mesh3D();
        ~Mesh3D();
        float* Vertices();
        unsigned int** Indeces();
        int* CountIndeces();
        int CountPrimitives();
        bool LoadOBJ(const char* path);
        void Scale(float scaleFactor);
    };
}}

#endif