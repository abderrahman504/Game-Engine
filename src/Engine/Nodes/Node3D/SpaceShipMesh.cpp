//
// Created by AhmedSamir on 15/05/2024.
//

#include "SpaceShipMesh.h"

using namespace Engine::Nodes;


SpaceShipMesh::SpaceShipMesh(float baseWidth, float baseHeight, float height, int resolution) {
    this->baseWidth = baseWidth;
    this->baseHeight = baseHeight;
    this->height = height;
   this->LoadOBJ("/home/ahmed/Downloads/Game-Engine/space2.obj",&vertices,&indeces,&countIndeces,&countPrimitives);
//    this->scale= Vector3(2,2,2);
    // buildMesh(baseWidth, baseHeight, height, resolution, &vertices,&texCoords, &indeces, &countIndeces, &countPrimitives);
    setName("SpaceShipMesh");
}



float SpaceShipMesh::BaseWidth() { return baseWidth; }

float SpaceShipMesh::BaseHeight() { return baseHeight; }

float SpaceShipMesh::Height() { return height; }

void SpaceShipMesh::buildMesh(float baseWidth, float baseHeight, float height, int resolution, float **vertices, float **texCoords, unsigned int ***indices, int **countIndices, int *countPrimitives) {
    *countPrimitives = resolution + 1;
    *countIndices = new int[resolution + 1];
    *indices = new unsigned int*[resolution + 1];
    for (int i = 0; i <= resolution; i++) {
        (*indices)[i] = new unsigned int[2 * (resolution + 1)];
        (*countIndices)[i] = 2 * (resolution + 1);
    }
    
    int numVertices = (resolution + 1) * (resolution + 1);
    *vertices = new float[numVertices * 3];
    *texCoords = new float[numVertices * 2];

    float stepSize = height / resolution;
    float angleIncrement = 2.0f * M_PI / resolution;

    int vertexIndex = 0;
    int texCoordIndex = 0;

    // Compute vertices and texture coordinates
    for (int i = 0; i <= resolution; i++) {
        float currentHeight = i * stepSize;
        float currentRadius = (baseWidth / 2) * (1.0f - currentHeight / height);
        float yCoord = -baseHeight / 2.0f + currentHeight;

        for (int j = 0; j <= resolution; j++) {
            float angle = j * angleIncrement;
            float xCoord = currentRadius * cos(angle);
            float zCoord = currentRadius * sin(angle);

            (*vertices)[vertexIndex++] = xCoord;
            (*vertices)[vertexIndex++] = zCoord;
            (*vertices)[vertexIndex++] = -yCoord;

            // Calculate texture coordinates
            (*texCoords)[texCoordIndex++] = (float)j / resolution;
            (*texCoords)[texCoordIndex++] = 1.0f - (float)i / resolution;
        }
    }

    // Generate indices
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j <= resolution; j++) {
            (*indices)[i][2 * j] = i * (resolution + 1) + j;
            (*indices)[i][2 * j + 1] = (i + 1) * (resolution + 1) + j;
        }
    }
}
