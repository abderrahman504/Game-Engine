#include "CylinderMesh.h"
#include <math.h>

using namespace Engine::Nodes;

void buildVertices(float radius, float height, int resolution, float**, unsigned int***, int**, int*);

CylinderMesh::CylinderMesh(float radius, float height, int resolution)
{
    this->radius = radius;
    this->height = height;
    buildVertices(radius, height, resolution, &vertices, &indeces, &countIndeces, &countPrimitives);
    setName("CylinderMesh");
}

float CylinderMesh::Radius(){return radius;}
float CylinderMesh::Height(){return height;}


void buildVertices(float radius, float height, int resolution, float **vertices, unsigned int ***indeces, int **countIndeces, int *countPrimitives)
{
    /* 
    Number of primatives:
    - 2 for top and bottom
    - 1 for the entire wall.
    */
    *countPrimitives = 3;
    *countIndeces = new int[3];
    *indeces = new unsigned int*[3];
    //Top and bottom indeces
    (*indeces)[0] = new unsigned int[2*(resolution+1)];
    (*indeces)[1] = new unsigned int[2*(resolution+1)];
    (*countIndeces)[0] = 2*(resolution+1);
    (*countIndeces)[1] = 2*(resolution+1);
    //Surface indeces
    (*indeces)[2] = new unsigned int[2*(resolution+1)];
    (*countIndeces)[2] = 2*(resolution+1);
    
    // i = 0: top center
    // i = [1, resolution]: top circle 
    // i = resolution + 1: bottom center
    // i = [resolution + 2, 2*resolution + 1]: bottom circle   
    *vertices = new float[(2 * (resolution+1)) * 3];
    
    float v;
    float top_y = height/2;
    float bottom_y = -top_y;
    //Calculating vertices
    (*vertices)[0] = 0;
    (*vertices)[1] = top_y;
    (*vertices)[2] = 0;
    
    (*vertices)[3 * (resolution+1) + 0] = 0;
    (*vertices)[3 * (resolution+1) + 1] = bottom_y;
    (*vertices)[3 * (resolution+1) + 2] = 0;

    for(int i = 0; i <= resolution; i++)
    {
        v = (float)i / resolution; //A value from 0 to 1.
        v = (v - 0.5) * 2; //A value from -1 to 1;
        float x = radius * cos(v * 2*PI);
        float z = radius * sin(v * 2*PI);
        (*vertices)[((i%resolution)+1)*3] = x;
        (*vertices)[((i%resolution)+1)*3 + 1] = top_y;
        (*vertices)[((i%resolution)+1)*3 + 2] = z;

        (*vertices)[(resolution+1 + (i%resolution)+1)*3] = x;
        (*vertices)[(resolution+1 + (i%resolution)+1)*3 + 1] = bottom_y;
        (*vertices)[(resolution+1 + (i%resolution)+1)*3 + 2] = z;
    }

    //Setting indeces
    //Top and Bottom
    for(int i = 0; i <= resolution; i++)
    {
        (*indeces)[0][2*i] = 0;
        (*indeces)[0][2*i + 1] = (i%resolution)+1;

        (*indeces)[1][2*i] = resolution+1;
        (*indeces)[1][2*i + 1] = resolution+1 + (i%resolution)+1;
    }
    //Wall
    for(int i = 0; i <= resolution; i++)
    {
        (*indeces)[2][2*i] = (i%resolution)+1;
        (*indeces)[2][2*i + 1] = resolution+1 + (i%resolution)+1;
    }
    
}