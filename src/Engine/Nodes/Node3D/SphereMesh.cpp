#include "SphereMesh.h"
#include <cmath>
#include <iostream>

using namespace Engine::Nodes;

void buildSphereVertices(float radius, int resolution, float **vertices, float **texCoords, unsigned int ***indices, int **countIndices, int *countPrimitives, int *texCoordsSize);

SphereMesh::SphereMesh(float radius, int resolution)
{
    this->radius = radius;
    buildSphereVertices(radius, resolution, &vertices, &texCoords, &indeces, &countIndeces, &countPrimitives, &texCoordsSize);
    setName("SphereMesh");
}

float SphereMesh::Radius() { return radius; }

void buildSphereVertices(float radius, int resolution, float **vertices, float **texCoords, unsigned int ***indices, int **countIndices, int *countPrimitives, int *texCoordsSize)
{
    *countPrimitives = resolution;
    *countIndices = new int[resolution];
    *indices = new unsigned int*[resolution];
    for (int i = 0; i < resolution; i++) {
        (*indices)[i] = new unsigned int[2 * (resolution + 1)];
        (*countIndices)[i] = 2 * (resolution + 1);
    }
    *vertices = new float[((resolution + 1) * (resolution + 1)) * 3];
    *texCoords = new float[((resolution + 1) * (resolution + 1)) * 2];
    *texCoordsSize = ((resolution + 1) * (resolution + 1)) * 2;

    int vertexIndex = 0;
    int texCoordIndex = 0;
    for (int i = 0; i <= resolution; i++) {
        float v = (float)i / resolution; // A value from 0 to 1.
        float theta = v * PI; // Polar angle.

        for (int j = 0; j <= resolution; j++) {
            float u = (float)j / resolution; // A value from 0 to 1.
            float phi = u * 2 * PI; // Azimuthal angle.

            float x = radius * sin(theta) * cos(phi);
            float y = radius * cos(theta);
            float z = radius * sin(theta) * sin(phi);

            (*vertices)[vertexIndex] = x;
            (*vertices)[vertexIndex + 1] = y;
            (*vertices)[vertexIndex + 2] = z;
            vertexIndex += 3;

            (*texCoords)[texCoordIndex] = u;
            (*texCoords)[texCoordIndex + 1] = 1.0f - v; // Flip v coordinate for correct texture orientation.
            texCoordIndex += 2;
        }
    }

    // Setting indices
    for (int slice = 0; slice < resolution; slice++) {
        for (int j = 0; j <= resolution; j++) {
            (*indices)[slice][2 * j] = slice * (resolution + 1) + j;
            (*indices)[slice][2 * j + 1] = (slice + 1) * (resolution + 1) + j;
        }
    }
}
