//
// Created by AhmedSamir on 15/05/2024.
//

#include "SpaceShipMesh.h"

using namespace Engine::Nodes;

SpaceShipMesh::SpaceShipMesh() {
    
    this->LoadOBJ("../resources/models/spaceship.obj",&vertices,&indeces,&countIndeces,&countPrimitives,&colors);
    setName("SpaceShipMesh");
}



