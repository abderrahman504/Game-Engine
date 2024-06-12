//
// Created by AhmedSamir on 15/05/2024.
//

#include "SpaceShipMesh.h"

using namespace Engine::Nodes;


SpaceShipMesh::SpaceShipMesh(float baseWidth, float baseHeight, float height, int resolution) {
    this->baseWidth = baseWidth;
    this->baseHeight = baseHeight;
    this->height = height;
    this->LoadOBJ("C:\\Users\\ahmed\\Desktop\\Game-Engine\\spaceship.obj");
    this->scale= Vector3(2,2,2);
//    buildMesh(baseWidth, baseHeight, height, resolution, &vertices, &indeces, &countIndeces, &countPrimitives);
    setName("SpaceShipMesh");
}



float SpaceShipMesh::BaseWidth() { return baseWidth; }

float SpaceShipMesh::BaseHeight() { return baseHeight; }

float SpaceShipMesh::Height() { return height; }

void SpaceShipMesh::buildMesh(float baseWidth, float baseHeight, float height, int resolution, float **vertices, unsigned int ***indeces, int **countIndeces, int *countPrimitives) {

    *countPrimitives = resolution + 1; // Add 1 for the base of the spaceship
    *countIndeces = new int[resolution + 1]; // Add 1 for the base of the spaceship
    *indeces = new unsigned int*[resolution + 1]; // Add 1 for the base of the spaceship
    for (int i =  0; i <= resolution; i++){ // Add 1 for the base of the spaceship
        (*indeces)[i] = new unsigned int[2*(resolution+1)];
        (*countIndeces)[i] = 2*(resolution+1);
    }
    *vertices = new float[((resolution+1) * (resolution + 1)) * 3];

    float stepSize = height / resolution;
    float angleIncrement = 2.0f * PI / resolution;

    // Generate vertices for the spaceship
    int vertexIndex = 0;
    for (int i = 0; i <= resolution; i++) {
        float currentHeight = i * stepSize;
        float currentRadius = (baseWidth / 2) * (1.0f - currentHeight / height);
        float yCoord = -baseHeight / 2.0f + currentHeight;

        for (int j = 0; j < resolution; j++) {
            float angle = j * angleIncrement;
            float xCoord = currentRadius * cos(angle);
            float zCoord = currentRadius * sin(angle);
            (*vertices)[vertexIndex++] = xCoord;
            (*vertices)[vertexIndex++] = zCoord;
            (*vertices)[vertexIndex++] = -yCoord;
        }
    }

    float baseRadius = baseWidth / 2;
    for (int j = 0; j < resolution; j++) {
        float angle = j * angleIncrement;
        float xCoord = baseRadius * cos(angle);
        float zCoord = baseRadius * sin(angle);
        float yCoord = -baseHeight / 2.0f; // Base is at the bottom of the cone
        (*vertices)[vertexIndex++] = xCoord;
        (*vertices)[vertexIndex++] = zCoord;
        (*vertices)[vertexIndex++] = yCoord;
    }

    // Generate indices for the spaceship
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j <= resolution; j++) {
            (*indeces)[i][2 * j] = i * resolution + j % resolution;
            (*indeces)[i][2 * j + 1] = (i + 1) * resolution + j % resolution;
        }
    }
    for (int j = 0; j < resolution; j++) {
        (*indeces)[resolution][2 * j] = resolution * resolution + j;
        (*indeces)[resolution][2 * j + 1] = resolution * resolution + (j + 1) % resolution;
    }

}
