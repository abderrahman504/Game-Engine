//
// Created by AhmedSamir on 15/05/2024.
//

#ifndef GAME_ENGINE_SPACESHIPMESH_H
#define GAME_ENGINE_SPACESHIPMESH_H


#include "Mesh3D.h"


namespace Engine {
    namespace Nodes {
        class SpaceShipMesh : public Mesh3D {
        protected:
            float baseWidth;
            float baseHeight;
            float height;

        public:
            SpaceShipMesh(float baseWidth, float baseHeight, float height, int resolution);

            ~SpaceShipMesh();   
            float BaseWidth();

            float BaseHeight();

            float Height();
        };
    }
}


#endif //GAME_ENGINE_SPACESHIPMESH_H
