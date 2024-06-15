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
    this->LoadOBJ("/home/ahmed/Downloads/Game-Engine/ahmedtest/elk-color.obj",&vertices,&indeces,&countIndeces,&countPrimitives,&colors);
    this->scale= Vector3(2,2,2);
    // buildMesh(baseWidth, baseHeight, height, resolution, &vertices,&texCoords, &indeces, &countIndeces, &countPrimitives);
    setName("SpaceShipMesh");
}



float SpaceShipMesh::BaseWidth() { return baseWidth; }

float SpaceShipMesh::BaseHeight() { return baseHeight; }

float SpaceShipMesh::Height() { return height; }

void buildMesh(float baseWidth, float baseHeight, float height, int resolution, float **vertices,float **texCoords ,unsigned int ***indeces, int **countIndeces, int *countPrimitives) 
{
    *countPrimitives = 2; //The top and bottom sides are 2 triangle strips. The inner and outer walls of the disk are 2 triangle strips.
    *countIndeces = new int[2];
    *indeces = new unsigned int*[2];
    //Base indices
    (*indeces)[0] = new unsigned int[2* (resolution+1)];
    (*countIndeces)[0] = 2* (resolution+1);

    //Wall indices
    (*indeces)[1] = new unsigned int[2* (resolution+1)];
    (*countIndeces)[1] = 2* (resolution+1);

    *vertices = new float[(2 + resolution) * 3]; //First 2 are the top and base center. the rest are vertices of the base.
    //Base center
    (*vertices)[0] = 0;
    (*vertices)[1] = 0;
    (*vertices)[2] = 0;
    //Top
    (*vertices)[3] = 0;
    (*vertices)[4] = height;
    (*vertices)[5] = 0;

    //Building vertices
    for(int i=0; i < resolution; i++)
    {
        float angle = 2 * PI * i / resolution;
        //Base
        (*vertices)[(2 + i)*3 + 0] = baseWidth * cos(angle);
        (*vertices)[(2 + i)*3 + 1] = 0;
        (*vertices)[(2 + i)*3 + 2] = baseHeight * sin(angle);
    }

    //Setting indices

    for(int i=0; i <= resolution; i++)
    {
        //Base indeces
        (*indeces)[0][2*i] = 0;
        (*indeces)[0][2*i + 1] = 2+(i%resolution);

        //Wall indeces
        (*indeces)[1][2*i] = 1;
        (*indeces)[1][2*i + 1] = 2+(i%resolution);

    }

}
