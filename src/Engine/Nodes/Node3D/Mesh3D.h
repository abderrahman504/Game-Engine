#ifndef MESH3D_GUARD
#define MESH3D_GUARD
#include "Node3D.h"

namespace Engine{
namespace Nodes{

    class Mesh3D : public Node3D
    {
        public:
        //True if the mesh was changed since the last time it was drawn.
        //Used to update any VAOs, VBOs, or display lists that are used to draw this mesh. 
        bool meshChanged = false;
        protected:
        //The vertices of the mesh
        float* vertices = nullptr;
        //The indeces of the mesh
        unsigned int** indeces = nullptr;
        int* countIndeces = nullptr;
        int countPrimatives = 0;
        
        public:
        Mesh3D();
        ~Mesh3D();
        float* Vertices();
        unsigned int** Indeces();
        int* CountIndeces();
        int CountPrimatives();
    };
}}

#endif