#include "SphereMesh.h"
#include <math.h>

using namespace Engine::Nodes;

void buildSphereVertices(float, int, float**, unsigned int***, int**, int*);

SphereMesh::SphereMesh(float radius, int resolution)
{
    this->radius = radius;
    buildSphereVertices(radius, resolution, &vertices, &indeces, &countIndeces, &countPrimitives);
    setName("SphereMesh");
}

float SphereMesh::Radius(){return radius;}



void buildSphereVertices(float radius, int resolution, float **vertices, unsigned int ***indeces, int **countIndeces, int *countPrimitives)
{
    *countPrimitives = resolution;
    *countIndeces = new int[resolution];
    *indeces = new unsigned int*[resolution];
    for (int i =  0; i < resolution; i++){
        (*indeces)[i] = new unsigned int[2*(resolution+1)];
        (*countIndeces)[i] = 2*(resolution+1);
    }
    *vertices = new float[((resolution+1) * (resolution)) * 3];
    
    float u, v;
    //Calculating vertices
    for(int i = 0; i <= resolution; i++)
    {
        v = (float)i / resolution; //A value from 0 to 1.
        v = (v - 0.5) * 2; //A value from -1 to 1;
        float slice_r = radius * cos(v * 2*PI);
        float y = radius * sin(v * 2*PI);
        for(int j = 0; j < resolution; j++)
        {
            u = (float)j / resolution; //A value from 0 to 1
            float x = slice_r * cos(u * 2*PI);
            float z = slice_r * sin(u * 2*PI);
            int vertex_index = resolution * (i) + j;
            (*vertices)[vertex_index*3] = x;
            (*vertices)[vertex_index*3 + 1] = y;
            (*vertices)[vertex_index*3 + 2] = z;
        }
    }

    //Setting indeces
    for(int slice = 0; slice < resolution; slice++)
    {
        for(int j = 0; j <= resolution; j++)
        {
            (*indeces)[slice][2*j] = slice*resolution + j%resolution;
            (*indeces)[slice][2*j + 1] = (slice+1)*resolution + j%resolution;
        }
    }
}