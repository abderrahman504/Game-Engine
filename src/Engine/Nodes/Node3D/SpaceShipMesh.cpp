//
// Created by AhmedSamir on 15/05/2024.
//

#include "SpaceShipMesh.h"

using namespace Engine::Nodes;

void buildMesh(float baseWidth, float baseHeight, float height, int resolution, float **vertices,float **texCoords ,unsigned int ***indices, int **countIndices, int *countPrimitives);

SpaceShipMesh::SpaceShipMesh(float baseWidth, float baseHeight, float height, int resolution) {
    this->baseWidth = baseWidth;
    this->baseHeight = baseHeight;
    this->height = height;
    this->LoadOBJ("../resources/models/spaceship.obj",&vertices,&indeces,&countIndeces,&countPrimitives,&colors);
    // this->scale= Vector3(2,2,2);
    // buildMesh(baseWidth, baseHeight, height, resolution, &vertices,&texCoords, &indeces, &countIndeces, &countPrimitives);
    setName("SpaceShipMesh");
}


