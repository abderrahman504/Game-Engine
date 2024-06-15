//
// Created by AhmedSamir on 15/05/2024.
//

#include "SpaceShipMesh.h"

using namespace Engine::Nodes;

SpaceShipMesh::SpaceShipMesh() {
   this->LoadOBJ("/home/ahmed/Downloads/Game-Engine/space2.obj",&vertices,&indeces,&countIndeces,&countPrimitives);
   this->scale= Vector3(2,2,2);
    setName("SpaceShipMesh");
}


