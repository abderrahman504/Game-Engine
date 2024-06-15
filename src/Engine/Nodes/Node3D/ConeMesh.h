//
// Created by AhmedSamir on 15/05/2024.
//

#ifndef CONE_MESH_H
#define CONE_MESH_H


#include "Mesh3D.h"


namespace Engine {
    namespace Nodes {
        class ConeMesh : public Mesh3D {
        protected:
            float baseWidth;
            float baseHeight;
            float height;

        public:
            ConeMesh(float baseWidth, float baseHeight, float height, int resolution);

            ~ConeMesh();   
            float BaseWidth();

            float BaseHeight();

            float Height();
        };
    }
}


#endif //GAME_ENGINE_SPACESHIPMESH_H
